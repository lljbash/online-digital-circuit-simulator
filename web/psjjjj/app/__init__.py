from flask import Flask
from flask_bootstrap import Bootstrap
from client import MyClient
from py2proto.module_pb2 import ChipModuleListProto
from py2proto.request_pb2 import RequestProto
from flask_login import LoginManager
from config import UPLOAD_FOLDER
import MySQLdb

app = Flask(__name__)
Bootstrap(app)
app.config.from_object('config')
init_cli = MyClient()
init_cli.connect()
init_request = RequestProto()
init_request.type = 2
init_cli.sendMessage(init_request)
modulelist = ChipModuleListProto()
#print init_cli.recvMessage()
modulelist.ParseFromString(init_cli.recvMessage())
in_module = modulelist.modules.add()
in_module.name = 'input'
in_module.pins.add()
out_module = modulelist.modules.add()
out_module.name = 'output'
out_module.pins.add()
lm = LoginManager()
lm.init_app(app)
lm.login_view = "login"
conn = MySQLdb.connect(host = 'localhost', user = 'root', passwd = 'psjjjj')
conn.select_db('test')
print "Database connected!"
from app import views
