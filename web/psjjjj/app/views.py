from app import app
from flask import render_template, redirect, flash
from .forms import VHDLForm
from client import MyClient
from request_pb2 import RequestProto

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
        flash('VHDL code : ' + form.VHDLCode.data)
        cli = MyClient()
        cli.connect()
        #request = RequestProto()
        #request.type = 1;
        #request.vhdl_code = form.VHDLCode.data
	request = form.VHDLCode.data
        cli.sendmessage(request)
        return redirect('/index')
    return render_template('addVHDL.html', form=form)

@app.route('/studio/grafical', methods=['GET', 'POST'])
def addGraph():
    if form.validate_on_submit():
        flash('VHDL code : ' + form.VHDLCode.data)
        cli = MyClient()
        cli.connect()
        request = RequestProto()
        request.type = 1;
        request.vhdl_code = form.VHDLCode.data
        cli.sendmessage(request)
        return redirect('/index')
    return render_template('addGraph', form=form)
