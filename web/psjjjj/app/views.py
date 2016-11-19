from app import app, admin_permission, stu_permission
from app import modulelist
from config import  UPLOAD_FOLDER
from flask import render_template, redirect, flash, url_for, send_from_directory, request, g, current_app
from werkzeug.utils import secure_filename
from .forms import VHDLForm, LoginForm,ResetPasswordForm, CheckPasswordForm, TaskForm
from client import MyClient
from activate import parse_activate, activate_to_svg
from py2proto.request_pb2 import RequestProto
from py2proto.circuit_parsing_result_pb2 import CircuitParsingResultProto
from py2proto.simulation_result_pb2 import SimulationResultProto
from py2proto.circuit_pb2 import CircuitProto
from database import tryToLogin, verifyPassword, saveTask, getTask, getTasklist, getSubmissionlist, saveSubmission, getUserInfo, saveProject, getModel, getVHDL
from model import User
from flask_login import login_user, logout_user, login_required, current_user
from flask.ext.principal import identity_loaded, RoleNeed, UserNeed, Principal, Identity, identity_changed, AnonymousIdentity
import json

@app.route('/index')
@login_required
def index():
    print 'now index............................'
    items = getTasklist()
    if getUserInfo('flag') == 1:
        return render_template('management.html', items = items)
    return render_template('index.html', items = items, userid = g.user.id)

@app.route('/', methods = ['GET', 'POST'])
@app.route('/login', methods = ['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        print request.form
        error = tryToLogin(request.form['id'], request.form['password'])
        if error == None:
            user = User(request.form['id'])
            login_user(user, remember = False)
            identity_changed.send(current_app._get_current_object(), identity=Identity(user.id))
            flash('You are logged in!')
            print 'goto index ...........................'
            return redirect(url_for('index'))
    if error != None:
        flash(error)
    return render_template('login.html')

@app.route('/logout')
@login_required
def logout():
    logout_user()
    identity_changed.send(current_app._get_current_object(), identity = AnonymousIdentity())
    return redirect(url_for('login'))


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

@app.route('/studio/vhdl/<itemID>', methods=['GET', 'POST'])
@stu_permission.require()
def addVHDL(itemID):
    if request.method == 'POST':
        f = request.files['file']
        f.save('../../tmp' + '/activation/' + g.user.id)
    return render_template('vhdl.html', itemID = itemID)

@app.route('/studio/graph/<itemID>', methods=['GET', 'POST'])
@stu_permission.require()
def addGraph(itemID):
    if request.method == 'POST':
        f = request.files['file']
        f.save('../../tmp' + '/activation/' + g.user.id)
    return render_template('graph.html', itemID = itemID)

@app.route('/studio/graph/<itemID>/<subID>', methods = ['GET', 'POST'])
@stu_permission.require()
def addGraph_sub(itemID, subID):
    return render_template('graph.html', itemID = itemID, submissionID = subID)

@app.route('/submitted/<filename>', methods=['GET', 'POST'])
def submitted(filename):
    return render_template('submitted.html', url = url_for('download', filename = filename))

@app.route('/download/<filename>')
@stu_permission.require()
def download(filename):
    print 'download'
    print filename
    return send_from_directory('../../../tmp/vcd', filename, as_attachment = True)

@app.route('/error/<error_message>')
def error(error_message):
    return render_template('error.html', info=error_message)

@app.route('/save', methods=['POST'])
def save():
    print request.data
    saveProject(request.data)
    return "test.txt"

@app.route('/submit', methods=['POST'])
def submit():
    request_proto = RequestProto()
    request_proto.type = 0;
    data = json.loads(request.data)
    models = data['data']
    itemID = data['itemID']
    nodes = models['nodes']
    edges = models['edges']
    map_dic = []
    f = open(UPLOAD_FOLDER + "/task/" + str(itemID))
    text = f.read()
    activationList = parse_activate(text)
    for i in range(100):
        map_dic.append([])
    for node in nodes:
        chip = request_proto.circuit.chips.add()
        chip.id = str(node['id'])
        chip.type = node['type']
        if chip.type=="input":
            for activation in activationList:
                if node['ano_name']==activation[0]:
                    chip.activation = activation[1]
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
    return "error"

@app.route('/test', methods=['POST'])
@stu_permission.require()
def test():
    request_proto = RequestProto()
    request_proto.type = 0;
    data = json.loads(request.data)
    models = data['data']
    itemID = data['itemID']
    nodes = models['nodes']
    edges = models['edges']
    map_dic = []
    f = open('../../tmp' + "/activation/" + str(g.user.id))
    text = f.read()
    activationList = parse_activate(text)
    for i in range(10000):
        map_dic.append([])
    for node in nodes:
        print node
        chip = request_proto.circuit.chips.add()
        chip.id = str(node['id'])
        chip.type = node['type']
        if chip.type=="input":
            for activation in activationList:
                if node['ano_name']==activation[0]:
                    chip.activation.initial = activation[1].initial
                    chip.activation.repeat = activation[1].repeat
                    chip.activation.jumping_time.extend(activation[1].jumping_time)
        connectors = node['connectors']
        pin_id = 0
        tot_size = len(connectors)
        up_size = (tot_size + 1) / 2
        down_size = tot_size / 2
        for connector in connectors:
            print connector
            if pin_id < up_size:
                real_id = up_size - pin_id - 1 + down_size
            else:
                real_id = pin_id - up_size
            map_dic[connector['id']] = [chip.id, real_id]
            pin_id = pin_id + 1
    for edge in edges:
        source = edge['source']
        destination = edge['destination']
        wire = request_proto.circuit.wires.add()
        wire.start_pin.chip_name = map_dic[source][0]
        wire.start_pin.pin_name = str(map_dic[source][1])
        wire.end_pin.chip_name = map_dic[destination][0]
        wire.end_pin.pin_name = str(map_dic[destination][1])
        print wire

    cli = MyClient()
    cli.connect()
    cli.sendMessage(request_proto)
    print request_proto
    reply = CircuitParsingResultProto()
    reply.ParseFromString(cli.recvMessage())
    cli.close(0)
    if reply.success:
        cli = MyClient()
        cli.connect()
        request_proto_2 = RequestProto()
        request_proto_2.type = 1
        request_proto_2.vhdl_code = reply.vhdl_code
        vhdl = reply.vhdl_code
        cli.sendMessage(request_proto_2)
        reply2 = SimulationResultProto()
        reply2.ParseFromString(cli.recvMessage())
        f = open('../../tmp' + '/vhdl/' + reply2.file_name, 'w')
        f.write(vhdl)
        f.close()
        f = open('../../tmp' + '/out/' + reply2.file_name, 'w')
        f.write(reply2.wave_info)
        f.close()
        return reply2.file_name
    return "error"

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
    if request.method == 'POST':
        taskID = saveTask(request.form)
        f = request.files['input']
        taskaddr = UPLOAD_FOLDER + '/tasks/' + str(taskID)
        f.save(taskaddr + '.in')
        f = request.files['output']
        f.save(taskaddr + '.ans')
        tasks = getTasklist()
        print request.form
        return redirect(url_for('index'))
    return render_template('addTask.html')

@app.route('/tasklist')
def tasklist():
    tasks = getTasklist()
    return render_template('tasklist.html', tasks = tasks)

@app.route('/detail/<itemID>')
def showTask(itemID):
    item = getTask(itemID)
    return render_template('detail.html', item = item)

@app.route('/submissionlist/<itemID>')
def submissionlist(itemID):
    submissions = getSubmissionlist(itemID)
    return render_template('submissionlist.html', submissions = submissions, itemID = itemID)

@app.before_request
def befor_request():
    g.user = current_user

@identity_loaded.connect_via(app)
def on_identity_load(sender, identity):
    identity.user = current_user
    if current_user.get_id() == None:
        print 'anonymous'        
	return
    if getUserInfo('flag') == 0:
        identity.provides.add(RoleNeed('stu'))
    if getUserInfo('flag') == 1:
        identity.provides.add(RoleNeed('admin'))

@app.route('/load', methods = ['POST'])
def load():
    if request.method == 'POST':
        data = json.loads(request.data)
        itemID = data['itemID']
        submissionID = data['submissionID']
        print submissionID
        return getModel(itemID, submissionID)

@app.route('/load_vhdl', methods = ['POST'])
def load_vhdl():
    if request.method == 'POST':
        print request.form
        data = json.loads(request.form['data'])
        itemID = data['itemID']
        submissionID = data['submissionID']
        print data
        print itemID
        return getVHDL(itemID, submissionID)

@app.route('/getVHDL/<filename>', methods = ['POST'])
def getVHDL_from_graph(filename):
    if request.method == 'POST':
        f = open('../../tmp' + '/vhdl/' + filename)
        vhdl = f.read()
        f.close()
        return vhdl
    return

@app.route('/showVHDL/<filename>')
def showVHDL(filename):
    return render_template('showVHDL.html')

@app.route('/showInput')
def showInput():
    f = open('../../tmp/activation/' + g.user.id)
    data = f.read()
    f.close()
    print data
    acts = parse_activate(data)
    print acts
    svg = activate_to_svg(acts)
    print svg
    return render_template('showinput.html', svg = svg, title = 'Input')

@app.route('/result/<filename>')
def showResult(filename):
    f = open('../../tmp/out/' + filename)
    data = f.read()
    f.close()
    acts = parse_activate(data)
    svg = activate_to_svg(acts)
    return render_template('showinput.html', svg = svg, title = 'Result')