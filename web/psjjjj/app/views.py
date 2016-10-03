from app import app
from flask import render_template

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

@app.route('/studio/vhdl')
def addVHDL():
    return render_template('addVHDL.html')

@app.route('/studio/grafical')
def addGraph():
    return render_template('addGraph')