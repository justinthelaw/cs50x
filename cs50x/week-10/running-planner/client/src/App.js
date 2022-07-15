// dependencies
import React, { useEffect, useState } from "react";
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Navigate,
} from "react-router-dom";
import AppContext from "./contexts/AppContext";
import { persist } from "./utils/account.js";

// components
import NavBar from "./components/NavBar.jsx";
import Home from "./components/Home.jsx";
import Login from "./components/Login.jsx";
import Register from "./components/Register.jsx";
import Templates from "./components/Templates.jsx";

import ProtectedRoute from "./utils/ProtectedRoute.jsx";

// styles
import "bootstrap/dist/css/bootstrap.min.css";
import "./App.css";

export default function App() {
  const [session, setSession] = useState({ auth: false });
  const [showAlert, setShowAlert] = useState(false);
  const [alertMessage, setAlertMessage] = useState("");
  const [alertType, setAlertType] = useState("");

  useEffect(() => {
    persist(setSession);
  }, [showAlert]);

  return (
    <AppContext.Provider
      value={{
        session,
        setSession,
        showAlert,
        setShowAlert,
        alertMessage,
        setAlertMessage,
        alertType,
        setAlertType,
      }}
    >
      <Router>
        <nav>
          <NavBar />
        </nav>
        <main>
          <Routes>
            <Route path="/" element={<Home />} />
            <Route
              path="/login"
              element={!session?.auth ? <Login /> : <Navigate to="/" replace />}
            />
            <Route path="/register" element={<Register />} />
            <Route
              path="/templates"
              element={<ProtectedRoute component={() => <Templates />} />}
            />
            <Route path="/*" element={<Navigate to="/" replace />} />
          </Routes>
        </main>
      </Router>
    </AppContext.Provider>
  );
}
