import os
from flask import Flask
from client import MyClient
from py2proto.module_pb2 import ChipModuleListProto
from py2proto.request_pb2 import RequestProto

app = Flask(__name__)
app.config.from_object('config')
app.jinja_env.variable_start_string = '{{ '
app.jinja_env.variable_end_string = ' }}'
init_cli = MyClient()
init_cli.connect()
init_request = RequestProto()
init_request.type = 2
init_cli.sendMessage(init_request)
modulelist = ChipModuleListProto()
init_cli.recvMessage()
#modulelist = modulelist.ParseFromString(init_cli.recvMessage())
from app import views
