import MySQLdb
import xlrd
import random, string
import hashlib

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

psw = raw_input("enter database password:")
print psw
conn = MySQLdb.connect(host = 'localhost', user = 'root', passwd = psw)
conn.select_db('test')
cursor = conn.cursor()
sql = 'delete from users'
cursor.execute(sql)
data = xlrd.open_workbook('users.xlsx')
sheet = data.sheet_by_index(0)
n = sheet.nrows
for i in range(0, n):
    user_id = sheet.cell(i,0).value
    user_flag = int(sheet.cell(i,1).value)
    if (user_flag == 0):
        user_id = str(int(user_id))
    salt = random_str()
    psw = getmd5(user_id, salt)
    sql = "insert into users (id, password, salt, flag) values('%s', '%s', '%s', %d)"%(user_id, psw, salt, user_flag)
    cursor.execute(sql)
cursor.close()
conn.commit()
conn.close()


