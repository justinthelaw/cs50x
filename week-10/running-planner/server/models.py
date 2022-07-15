from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()


class UserModel(db.Model):
    __tablename__ = 'users'

    CONSTANTS = {
        "NAME_MIN": 1,
        "NAME_MAX": 50,
        "PASS_MIN": 8,
        "PASS_MAX": 50,
    }

    def constants(self):
        return self.CONSTANTS

    def check(self, name, password):
        c = self.CONSTANTS
        if len(name) >= c["NAME_MIN"] and len(name) <= c["NAME_MAX"] and len(
                password) >= c["PASS_MIN"] and len(password) <= c["PASS_MAX"]:
            return True
        else:
            return False

    id = db.Column(db.Integer, primary_key=True, unique=True)
    username = db.Column(db.String(CONSTANTS["NAME_MAX"] + 1),
                         unique=True,
                         nullable=False)
    password = db.Column(db.String(CONSTANTS["PASS_MAX"] + 1),
                         unique=True,
                         nullable=False)
    templates = db.relationship("TemplateModel",
                                backref="users",
                                cascade="all, delete, delete-orphan",
                                lazy=True)

    def __init__(self, username=None, password=None):
        self.username = username
        self.password = password

    def __repr__(self):
        return "<UserModel(id='%i', username='%s')>" % (self.id, self.username)

    def serialize(self):
        return {"id": self.id, "username": self.username}


class TemplateModel(db.Model):
    __tablename__ = 'templates'

    CONSTANTS = {
        "TITLE_MIN": 1,
        "TITLE_MAX": 50,
        "URL_MIN": 0,
        "URL_MAX": 200,
        "DESC_MIN": 1,
        "DESC_MAX": 500,
        "AMOUNT_MIN": 1,
        "AMOUNT_MAX": 1000,
        "VALID_UNITS": ["reps", "seconds", "minutes", "hours"],
    }

    def constants(self):
        return self.CONSTANTS

    def check(self, title, url, desc, amount, units):
        c = self.CONSTANTS
        if len(title) <= c["TITLE_MAX"] and len(
                title) >= c["TITLE_MIN"] and len(url) <= c["URL_MAX"] and len(
                    url) >= c["URL_MIN"] and len(desc) <= c[
                        "DESC_MAX"] and len(desc) >= c["DESC_MIN"] and len(
                            amount) <= c["AMOUNT_MAX"] and len(amount) >= c[
                                "AMOUNT_MIN"] and units in c["VALID_UNITS"]:
            return True
        else:
            return False

    id = db.Column(db.Integer, primary_key=True, unique=True)
    owner_id = db.Column(db.Integer, db.ForeignKey("users.id"), nullable=False)
    title = db.Column(db.String(CONSTANTS["TITLE_MAX"] + 1), nullable=False)
    url = db.Column(db.String(CONSTANTS["URL_MAX"] + 1), nullable=True)
    description = db.Column(db.String(CONSTANTS["DESC_MAX"] + 1),
                            nullable=False)
    units = db.Column(db.String(10), nullable=False)
    amount = db.Column(db.Integer, nullable=False)

    def __init__(self,
                 owner_id=None,
                 title=None,
                 url=None,
                 description=None,
                 amount=None,
                 units=None):
        self.owner_id = owner_id
        self.title = title
        self.url = url
        self.description = description
        self.amount = amount
        self.units = units

    def __repr__(self):
        return "<TemplateModel(id='%i', owner_id='%i', title='%s', url='%s', description='%s', amount='%i', units='%s')>" % (
            self.id,
            self.owner_id,
            self.title,
            self.url,
            self.description,
            self.amount,
            self.units,
        )

    def serialize(self):
        return {
            "id": self.id,
            "owner_id": self.owner_id,
            "title": self.title,
            "url": self.url,
            "description": self.description,
            "units": self.units,
            "amount": self.amount,
        }
