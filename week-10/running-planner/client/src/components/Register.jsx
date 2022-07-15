// dependencies
import React, { useState, useEffect, useContext } from "react";
import { useNavigate } from "react-router-dom";
import AppContext from "../contexts/AppContext";
import { handlePost } from "../utils/fetch.js";
import { getConstants } from "../utils/constants.js";

// bootstrap
import { Form, Button, Alert } from "react-bootstrap";

// styles
import "../styles/Account.css";

export default function Register() {
  const {
    showAlert,
    setShowAlert,
    alertMessage,
    setAlertMessage,
    alertType,
    setAlertType,
  } = useContext(AppContext);

  const [constants, setConstants] = useState(null);
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [confirmation, setConfirmation] = useState("");
  const [validName, setValidName] = useState(true);
  const [validPass, setValidPass] = useState(true);
  const [validConfirm, setValidConfirm] = useState(true);

  const navigate = useNavigate();

  useEffect(() => {
    getConstants("registration", setConstants);
  }, []);

  const validateUsername = (username) =>
    username.length >= constants.NAME_MIN &&
    username.length <= constants.NAME_MAX
      ? setValidName(true)
      : setValidName(false);

  const validatePassword = (password) =>
    password.length >= constants.PASS_MIN &&
    password.length <= constants.PASS_MAX
      ? setValidPass(true)
      : setValidPass(false);

  const validateConfirmation = (confirmation) =>
    password === confirmation ? setValidConfirm(true) : setValidConfirm(false);

  const validateForm = () =>
    username &&
    password &&
    confirmation &&
    validName &&
    validPass &&
    validConfirm;

  const callback = () => navigate("/");

  function handleSubmit(event) {
    event.preventDefault();
    const data = { username: username, password: password };
    handlePost(
      data,
      "/api/register",
      setAlertMessage,
      setAlertType,
      setShowAlert,
      callback
    );
  }

  return constants ? (
    <div className="register">
      <Form onSubmit={handleSubmit}>
        <Form.Group className="input" size="lg" controlId="username">
          <Form.Label>Username</Form.Label>
          <Form.Control
            autoFocus
            required
            type="username"
            value={username}
            isInvalid={!validName}
            onChange={(e) => {
              setUsername(e.target.value);
              validateUsername(e.target.value);
            }}
          />
          <Form.Control.Feedback type="invalid">
            Username must be {constants.NAME_MIN} to {constants.NAME_MAX}{" "}
            characters long
          </Form.Control.Feedback>
        </Form.Group>
        <Form.Group className="input" size="lg" controlId="password">
          <Form.Label>Password</Form.Label>
          <Form.Control
            required
            type="password"
            value={password}
            isInvalid={!validPass}
            onChange={(e) => {
              setPassword(e.target.value);
              validatePassword(e.target.value);
            }}
          />
          <Form.Control.Feedback type="invalid">
            Password must be {constants.PASS_MIN} to {constants.PASS_MAX}{" "}
            characters long
          </Form.Control.Feedback>
        </Form.Group>
        <Form.Group className="input" size="lg" controlId="confirmation">
          <Form.Label>Re-Type Password</Form.Label>
          <Form.Control
            required
            type="password"
            value={confirmation}
            isInvalid={!validConfirm}
            onChange={(e) => {
              setConfirmation(e.target.value);
              validateConfirmation(e.target.value);
              validatePassword(password);
            }}
          />
          <Form.Control.Feedback type="invalid">
            Passwords do not match
          </Form.Control.Feedback>
        </Form.Group>
        <Button
          className="button"
          size="md"
          type="submit"
          disabled={!validateForm()}
        >
          Register
        </Button>
        {showAlert && (
          <Alert
            className="alert"
            variant={alertType}
            dismissible
            onClose={() => setShowAlert(false)}
          >
            {alertMessage}
          </Alert>
        )}
      </Form>
    </div>
  ) : (
    <div className="register d-flex justify-content-center">
      <div className="spinner-border" role="status" />
    </div>
  );
}
