from flask.ext.wtf import Form
from wtforms import StringField, BooleanField
from wtforms.validators import DataRequired

class VHDLForm(Form):
    VHDLCode = StringField('VHDLCode', validators=[DataRequired()])
