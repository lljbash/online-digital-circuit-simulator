import MySQLdb
import hashlib
from app import conn
import random, string
from forms import TaskForm
from config import UPLOAD_FOLDER
from flask import g
from flask_login import current_user
import os
import time
from item import Item, Submission
import json

def tryToLogin(name, password):
    cursor = conn.cursor()
    sql = "select salt, password from users where id = '%s'"%(name)
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
    sql = "update users set salt = '%s' where id = '%s'"%(salt, name)
    cursor.execute(sql)
    sql = "update users set password = '%s' where id = '%s'" %(new_hash_password, name)
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
    addr = UPLOAD_FOLDER + '/tasks/' + form.title.data
    sql = "select * from tasks where title = '%s'"%(form.title.data)
    cursor.execute(sql)
    data = cursor.fetchall()
    #if data != None:
    #    return 'title exists'
    sql = "insert tasks values('%s', '%s')"%(form.title.data, addr)
    cursor.execute(sql)
    cursor.close()
    conn.commit()
    os.makedirs(addr)
    form.content.data.save(addr + '/content')
    return None

def getTask(taskID):
    cursor = conn.cursor()
    sql = "select title, detail from tasks where id = %s"%(taskID)
    cursor.execute(sql)
    data = cursor.fetchone()
    cursor.close()
    item = Item()
    item.title = data[0]
    item.detail = data[1]
    item.itemID = taskID
    return item

def getTasklist():
    cursor = conn.cursor()
    sql = "select id, title, abstract from tasks"
    cursor.execute(sql)
    data = cursor.fetchall()
    tasklist = []
    for task in data:
        item = Item()
        item.itemID = task[0]
        item.title = task[1]
        item.abstract = task[2]
        tasklist.append(item)      
    cursor.close()
    return tasklist
    
#save and get submission
def getSubmissionlist(itemID):
    cursor = conn.cursor()
    sql = "select title from tasks where id = '%s'"%(itemID)
    cursor.execute(sql)
    data = cursor.fetchone()
    title = data[0]
    sql = "select time, result, id from submissions where author = '%s' and task = '%s'"%(g.user.id, itemID)
    cursor.execute(sql)
    data = cursor.fetchall()
    cursor.close()
    sublist = []
    for sub in data:
        submission = Submission()
        submission.title = title
        submission.time = sub[0]
        submission.status = sub[1]
        submission.submissionID = sub[2]
        sublist.append(submission)
    return sublist

def getSubmission(sub_id):
    cursor = conn.cursor()
    sql = "select * from submissions where id = '%s'"%(sub_id)
    cursor.execute(sql)
    data = cursor.fetchone()
    cursor.close()
    return data

def saveSubmission(subID, data):
    author = g.user.id
    save_time = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
    task = '0'
    cursor = conn.cursor()
    sql = "insert submissions (id, author, time, task, result) values('%s', '%s', '%s', '%s', 'AC')"\
           %(subID, author, save_time, task)
    f = open(UPLOAD_FOLDER + "/graph/" + subID + ".json", 'w')
    f.write(data)
    f.close()
    cursor.execute(sql)
    cursor.close()
    conn.commit()
    
    
def getUserInfo(field):
    userid = current_user.id
    cursor = conn.cursor()
    sql = "select %s from users where id = %s"%(field, userid)
    cursor.execute(sql)
    data = cursor.fetchone()
    return data[0]

def saveProject(request_data):
    data = json.loads(request_data)
    itemID = data['itemID']
    author = g.user.id
    saveID = getmd5(author + str(itemID), '158647')
    save_time = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
    task = 'task'
    cursor = conn.cursor()
    sql = "insert savedfiles (id, author, time, task) values('%s', '%s', '%s', '%s')"\
           %(saveID, author, save_time, itemID)
    f = open(UPLOAD_FOLDER + "/graph/" + saveID + ".json", 'w')
    f.write(request_data)
    f.close()
    cursor.execute(sql)
    cursor.close()
    conn.commit()

def getModel(itemID, submissionID):
    author = g.user.id
    saveID = getmd5(author + itemID, '158647')
    if submissionID != '':
        saveID = submissionID
    print submissionID
    cursor = conn.cursor()
    try: 
        #saveID = '13e9a4962d7e0815e4af851608f49d73'
        f = open(UPLOAD_FOLDER + "/graph/" + saveID + ".json", 'r' )
        data = f.read()
        data = json.loads(data)       
        model = data['data']
        model = json.dumps(model)
        f.close()
        return model
    except:
        model = '{"nodes":[], "edges":[]}'
        #model = json.dumps(model)
        return model

