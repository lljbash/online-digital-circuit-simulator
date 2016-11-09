import MySQLdb
import hashlib
from app import conn
import random, string
from forms import TaskForm
from config import UPLOAD_FOLDER
from flask import g
import os
import time

def tryToLogin(name, password):
    cursor = conn.cursor()
    sql = "select salt, password from students where id = '%s'"%(name)
    cursor.execute(sql)  
    data = cursor.fetchone()
    cursor.close()
    if data == None:
        return "Wrong username!"
    psw = getmd5(password, data[0])
    if psw != data[1]:
        return "Wrong password!"
    return None

def verifyPassword(name, password):
    cursor = conn.cursor()
    salt = random_str(6)
    new_hash_password = getmd5(password, salt)
    sql = "update students set salt = '%s' where id = '%s'"%(salt, name)
    cursor.execute(sql)
    sql = "update students set password = '%s' where id = '%s'" %(new_hash_password, name)
    cursor.execute(sql)
    conn.commit()
    
def getmd5(src, salt):
    m = hashlib.md5()
    m.update(src)
    psw = m.hexdigest()
    m1 = hashlib.md5()
    m1.update(psw)
    m1.update(salt)
    return m1.hexdigest()

def random_str(randomlength=6):
    a = list(string.ascii_letters)
    random.shuffle(a)
    return ''.join(a[:randomlength])

#save and get task
def saveTask(form):
    cursor = conn.cursor()
    addr = UPLOAD_FOLDER + '/' + form.title.data
    sql = "insert tasks values('%s', '%s')"%(form.title.data, addr)
    cursor.execute(sql)
    cursor.close()
    conn.commit()
    os.makedirs(addr)
    form.content.data.save(addr + '/content')

def getTask(taskname):
    cursor = conn.cursor()
    sql = "select taskdir from tasks where title = '%s'"%(taskname)
    cursor.execute(sql)
    data = cursor.fetchone()
    cursor.close()    
    addr = data[0]
    fileobj = open(addr + '/content')
    try:
        content_md = fileobj.read()
    finally:
        fileobj.close()
    return content_md

def getTasklist():
    cursor = conn.cursor()
    sql = "select title from tasks"
    cursor.execute(sql)
    data = cursor.fetchall()
    tasklist = []
    for task in data:
        tasklist.append(task[0])
    cursor.close()
    return tasklist
    
#save and get submission
def getSubmissionlist(name)
    cursor = conn.cursor()
    sql = "select * from submissions where author = '%s'"%(name)
    cursor.execute(sql)
    data = cursor.fetchall()
    cursor.close()
    return data

def getSubmission(sub_id)
    cursor = conn.cursor()
    sql = "select * from submissions where id = '%s'"%(sub_id)
    cursor.execute(sql)
    data = cursor.fetchone()
    cursor.close()
    return data

def saveSubmission()
    author = g.user.id
    time = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
    id_time = time.strftime('%Y%m%d%H%M%S',time.localtime(time.time()))
    sub_id = id_time + author
    result = 'accepted'
    task = 'task'
    cursor = conn.cursor()
    sql = "insert into submissions values('%s', '%s', '%s', '%s', '%s')"%(sub_id, author, time, task, result)
    cursor.execute(sql)
    cursor.close()
    conn.commit()
    
    
