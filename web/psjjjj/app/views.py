from app import app, admin_permission, stu_permission
from app import modulelist
from flask import render_template, redirect, flash, url_for, send_from_directory, request, g, current_app
from werkzeug.utils import secure_filename
from .forms import VHDLForm, LoginForm,ResetPasswordForm, CheckPasswordForm, TaskForm
from client import MyClient
from py2proto.request_pb2 import RequestProto
from py2proto.circuit_parsing_result_pb2 import CircuitParsingResultProto
from py2proto.simulation_result_pb2 import SimulationResultProto
from py2proto.circuit_pb2 import CircuitProto
from database import tryToLogin, verifyPassword, saveTask, getTask, getTasklist, getSubmissionlist, saveSubmission, getUserInfo, saveProject, getModel
from model import User
from flask_login import login_user, logout_user, login_required, current_user
from flask.ext.principal import identity_loaded, RoleNeed, UserNeed, Principal, Identity, identity_changed
import json


@app.route('/')
@app.route('/index')
def index():
    items = getTasklist()
    return render_template('index.html', items = items, userid = g.user.id)

@app.route('/login', methods = ['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        error = tryToLogin(request.form['id'], request.form['password'])
        if error == None:
            user = User(request.form['id'])
            login_user(user, remember = False)
            identity_changed.send(current_app._get_current_object(), identity=Identity(user.id))
            flash('You are logged in!')
            return redirect(url_for('index'))
    if error != None:
        flash(error)
    return render_template('login.html')

@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('index'))


@app.route('/account/resetPassword/check', methods=['GET', 'POST'])
@login_required
def checkPassword():
    form = CheckPasswordForm()
    if request.method == 'POST':
        psw = form.password.data
        if tryToLogin(g.user.id, psw) == None:
            return redirect(url_for('resetPassword'))
        else:
            flash('Wrong password. Try again.')
    return render_template('checkPassword.html', form = form)

@app.route('/account/resetPassword/reset', methods=['GET', 'POST'])
@login_required
def resetPassword():
    form = ResetPasswordForm()
    if request.method == 'POST':
        psw = form.password.data
        flash('successfully reset your password!')
        verifyPassword(g.user.id, psw)
        return redirect(url_for('index'))
    return render_template('resetPassword.html', form = form)

@app.route('/account')
@login_required
def account():
    return render_template('account.html')

@app.route('/studio')
def addProject():
    return render_template('studio.html')

@app.route('/studio/vhdl', methods=['GET', 'POST'])
@stu_permission.require()
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
        if reply.success:
            return redirect(url_for('submitted', filename = reply.file_name))
        else:
            return redirect(url_for('error', error_message = reply.error_message))
    return render_template('vhdl.html', form=form)

@app.route('/studio/graph/<itemID>', methods=['GET', 'POST'])
@stu_permission.require()
def addGraph(itemID):
    return render_template('graph.html')

@app.route('/submitted/<filename>', methods=['GET', 'POST'])
def submitted(filename):
    return render_template('submitted.html', url = url_for('download', filename = filename))

@app.route('/download/<filename>')
def download(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename, as_attachment = True)

@app.route('/error/<error_message>')
def error(error_message):
    return render_template('error.html', info=error_message)

@app.route('/save', methods=['POST'])
def save():
    saveProject(request.data)
    return "test.txt"

@app.route('/submit', methods=['POST'])
def test():
    request_proto = RequestProto()
    request_proto.type = 0;
    data = json.loads(request.data)
    models = data['data']
    activation = data['activation'];
    nodes = models['nodes']
    map_dic = []
    for i in range(100):
        map_dic.append([])
    for node in nodes:
        chip = request_proto.circuit.chips.add()
        chip.id = str(node['id'])
        chip.type = node['name']
        if chip.type=="input":
            for input_unit in activation:
                if str(input_unit['id'])==chip.id:
                    chip.activation.initial = input_unit['input']
        connectors = node['connectors']
        pin_id = 0
        tot_size = len(connectors)
        up_size = (tot_size + 1) / 2
        down_size = tot_size / 2
        for connector in connectors:
            if pin_id < up_size:
                real_id = up_size - pin_id - 1 + down_size
            else:
                real_id = pin_id - up_size
            map_dic[connector['id']] = [chip.id, real_id]
            pin_id = pin_id + 1
    edges = models['edges']
    for edge in edges:
        source = edge['source']
        destination = edge['destination']
        wire = request_proto.circuit.wires.add()
        wire.start_pin.chip_name = map_dic[source][0]
        wire.start_pin.pin_name = str(map_dic[source][1])
        wire.end_pin.chip_name = map_dic[destination][0]
        wire.end_pin.pin_name = str(map_dic[destination][1])
    cli = MyClient()
    cli.connect()
    cli.sendMessage(request_proto)
    reply = CircuitParsingResultProto()
    reply.ParseFromString(cli.recvMessage())
    cli.close(0)
    if reply.success:
        cli = MyClient()
        cli.connect()
        request_proto_2 = RequestProto()
        request_proto_2.type = 1
        request_proto_2.vhdl_code = reply.vhdl_code
        cli.sendMessage(request_proto_2)
        reply = SimulationResultProto()
        reply.ParseFromString(cli.recvMessage())
        saveSubmission(reply.file_name, request.data)
        if reply.success:
            return reply.file_name
    return "test.txt"

@app.route('/add', methods=['POST'])
def add():
    data = json.loads(request.data)
    nodeName = data['data']
    pins_num = 0
    for module in modulelist.modules:
        if module.name==nodeName:
            for pin in module.pins:
                pins_num = pins_num + 1
            return str(pins_num)
    return '8'


@app.route('/addTask', methods=['GET', 'POST'])
@admin_permission.require()
def addTask():
    form = TaskForm()
    if request.method == 'POST':
        message = saveTask(form)
        if message != None:
            flash(message)
            return render_template('addTask.html', form = form)
        tasktitle = form.title.data
        flash('Successfully add task <' + tasktitle + '>')
        return redirect(url_for('tasklist'))
    return render_template('addTask.html', form = form)

@app.route('/tasklist')
def tasklist():
    tasks = getTasklist()
    return render_template('tasklist.html', tasks = tasks)

@app.route('/detail/<taskID>')
def showTask(taskID):
    item = getTask(taskID)
    return render_template('detail.html', item = item)

@app.route('/submissionlist')
def submissionlist():
    submissions = getSubmissionlist(g.user.id)
    return render_template('submissionlist.html', submissions = submissions)

@app.before_request
def befor_request():
    g.user = current_user

@identity_loaded.connect_via(app)
def on_identity_load(sender, identity):
    identity.user = current_user
    if getUserInfo('flag') == 0:
        identity.provides.add(RoleNeed('stu'))
    if getUserInfo('flag') == 1:
        identity.provides.add(RoleNeed('admin'))

@app.route('/load')
def load():
    if request.method == 'POST':
        data = json.loads(request.data)
        itemID = data['itemID']
        return getModel(itemID)
