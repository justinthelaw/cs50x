// dependencies
import React, { useState, useContext } from "react";
import AppContext from "../contexts/AppContext";
import { handlePost } from "../utils/fetch.js";
import { useNavigate } from "react-router-dom";

// bootstrap
import { Form, Button, Alert } from "react-bootstrap";

// styles
import "../styles/Account.css";

export default function Login({ forbidden }) {
  const {
    showAlert,
    setShowAlert,
    alertMessage,
    setAlertMessage,
    alertType,
    setAlertType,
  } = useContext(AppContext);

  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");

  const navigate = useNavigate();

  function validateForm() {
    return username && password;
  }
  const callback = () => (forbidden ? window.location.reload() : navigate("/"));

  function handleSubmit(event) {
    event.preventDefault();
    const data = { username: username, password: password };
    handlePost(
      data,
      "/api/login",
      setAlertMessage,
      setAlertType,
      setShowAlert,
      callback
    );
  }

  return (
    <div className={forbidden ? "forbidden" : "login"}>
      {forbidden && (
        <React.Fragment>
          <Alert className="access-forbidden" variant="warning">
            <Alert.Heading>[403] Access Forbidden</Alert.Heading>
            Please Login
          </Alert>
          <br />
        </React.Fragment>
      )}
      <Form onSubmit={handleSubmit}>
        <Form.Group className="input" size="lg" controlId="username">
          <Form.Label>Username</Form.Label>
          <Form.Control
            autoFocus
            type="username"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
          />
        </Form.Group>
        <Form.Group className="input" size="lg" controlId="password">
          <Form.Label>Password</Form.Label>
          <Form.Control
            type="password"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
          />
        </Form.Group>
        <Button
          className="button"
          size="md"
          type="submit"
          disabled={!validateForm()}
        >
          Login
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
  );
}
