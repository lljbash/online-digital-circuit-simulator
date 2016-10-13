from flask.ext.wtf import Form
from wtforms import StringField, BooleanField, TextAreaField
from wtforms.validators import DataRequired

class VHDLForm(Form):
    VHDLCode = TextAreaField('VHDLCode', validators=[DataRequired()])
