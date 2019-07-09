from flask.ext.wtf import Form
from wtforms import StringField, BooleanField, TextAreaField, PasswordField, FileField
from wtforms.validators import DataRequired
from wtforms import validators
from flask.ext.wtf.file import FileAllowed

class VHDLForm(Form):
    VHDLCode = TextAreaField('VHDLCode', validators=[DataRequired()])

class LoginForm(Form):
    name = StringField('name', validators = [DataRequired()])
    password = PasswordField('password', validators = [DataRequired()])

class CheckPasswordForm(Form):
    password = PasswordField('New Password', validators = [DataRequired()])


class ResetPasswordForm(Form):
    password = PasswordField('password', [
        validators.Required(),
        validators.EqualTo('confirm', message = 'Password must match')
    ])    
    confirm = PasswordField('Repeat Password', validators = [DataRequired()])

class TaskForm(Form):
    title = StringField('title', validators = [DataRequired()])
    content = FileField('file', validators = [
        validators.Required(),
        FileAllowed(['txt', 'md'], 'txt or md file')
    ])
    input_file = FileField('file')
    output_file = FileField('file')
