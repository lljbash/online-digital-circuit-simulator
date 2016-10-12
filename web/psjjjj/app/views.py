from app import app
from flask import render_template, redirect, flash, url_for, send_from_directory, request
from .forms import VHDLForm
from client import MyClient
from py2proto.request_pb2 import RequestProto
from py2proto.vhdl_parsing_result_pb2 import VHDLParsingResultProto
from py2proto.simulation_result_pb2 import SimulationResultProto
import json

@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/login')
def login():
    return render_template('login.html')

@app.route('/studio')
def addProject():
    return render_template('studio.html')

@app.route('/studio/vhdl', methods=['GET', 'POST'])
def addVHDL():
    form = VHDLForm()
    if form.validate_on_submit():
        cli = MyClient()
        cli.connect()
        request = RequestProto()
        request.type = 1
        request.vhdl_code = form.VHDLCode.data
        cli.sendMessage(request)
        reply = SimulationResultProto()
        reply.ParseFromString(cli.recvMessage())    
        flash('from server : ')
        flash('success : ' + str(reply.success))
        flash('file_name : ' + reply.file_name)
        return redirect(url_for('submitted', filename = reply.file_name))
    return render_template('addVHDL.html', form=form)

@app.route('/studio/graph', methods=['GET', 'POST'])
def addGraph():
    form = VHDLForm()
    if form.validate_on_submit():
        cli = MyClient()
        cli.connect()
        request = RequestProto()
        request.type = 0
        cli.sendMessage(request)
        reply = VHDLParsingResultProto()
        reply.ParseFromString(cli.recvMessage())
        flash('form server : ')
        flash('success : ' + str(reply.success))
        flash('vhdl_code : ' + reply.vhdl_code)
        return redirect('submitted')
    return render_template('addGraph.html', form=form)

@app.route('/submitted/<filename>', methods=['GET', 'POST'])
def submitted(filename):
    return render_template('submitted.html', url = url_for('download', filename = filename))

@app.route('/download/<filename>')
def download(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename, as_attachment = True)

@app.route('/test', methods=['POST'])
def test():
    if request.method == 'POST':
        data = json.loads(request.data)
        models = data['data']
	nodes = models['nodes']
        print nodes
        return "example.txt"
