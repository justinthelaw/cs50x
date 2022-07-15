from flask import session
from functools import wraps


# wrapper function to do server-side check of user log-in
def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return {"error": "You must login to use this feature."}
        return f(*args, **kwargs)

    return decorated_function