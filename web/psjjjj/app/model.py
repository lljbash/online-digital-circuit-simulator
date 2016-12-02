from app import lm
@lm.user_loader
def load_user(userid):
    return User.get(userid)

class User():
    id = ''
    def __init__(self, userid):
    	self.id = userid
    def is_authenticated(self):
        return True
    def is_active(self):
        return True
    def is_anonymous(self):
        return False
    def get_id(self):
        return unicode(self.id)
    @staticmethod
    def get(userid):
        user = User(userid.encode())
        return user

