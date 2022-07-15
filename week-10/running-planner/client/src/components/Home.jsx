// dependencies
import React, { useContext } from "react";
import AppContext from "../contexts/AppContext";

// components
import Welcome from "./Welcome.jsx";
import Explain from "./Explain.jsx";

// bootstrap
import { Alert } from "react-bootstrap";

// styles
import "../styles/Home.css";

export default function Home() {
  const { session, showAlert, setShowAlert, alertMessage, alertType } =
    useContext(AppContext);

  return (
    <div className={showAlert ? "home-alert" : "home"}>
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
      <Welcome auth={session.auth} />
      <Explain />
    </div>
  );
}
