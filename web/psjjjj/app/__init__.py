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
#print init_cli.recvMessage()
modulelist.ParseFromString(init_cli.recvMessage())
in_module = modulelist.modules.add()
in_module.name = 'input'
in_module.pins.add()
out_module = modulelist.modules.add()
out_module.name = 'output'
out_module.pins.add()
from app import views
