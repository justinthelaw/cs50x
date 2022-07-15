// dependencies
import React, { useContext } from "react";
import AppContext from "../contexts/AppContext";
import { Link, useNavigate } from "react-router-dom";
import { handleLogout } from "../utils/account.js";

// styles
import "../styles/NavBar.css";

// bootstrap
import { Navbar, Container, Nav } from "react-bootstrap";

export default function NavBar() {
  const { session, setSession, setShowAlert, setAlertType, setAlertMessage } =
    useContext(AppContext);

  const navigate = useNavigate();

  const handleClick = () => {
    setShowAlert(false);
  };

  async function onLogout(event) {
    event.preventDefault();
    setShowAlert(false);
    await handleLogout(setSession, setShowAlert, setAlertType, setAlertMessage);
    navigate("/");
  }

  return (
    <Navbar bg="dark" variant="dark" expand="lg" className="navbar">
      <Container fluid>
        <Link to="/" className="link" onClick={handleClick}>
          <Navbar.Brand className="navbar-brand">
            <img
              alt="Running Planner"
              src="/favicon.ico"
              width="45"
              height="42.5"
              className="d-inline-block align-middle"
            />
            Running Planner
          </Navbar.Brand>
        </Link>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
        <Navbar.Collapse id="basic-navbar-nav">
          <Nav className="me-auto">
            <div className="link-wrapper" onClick={handleClick}>
              <Link to="/" className="link">
                Home
              </Link>
            </div>
            {!session?.auth ? (
              <React.Fragment>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/login" className="link">
                    Login
                  </Link>
                </div>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/register" className="link">
                    Register
                  </Link>
                </div>
              </React.Fragment>
            ) : (
              <React.Fragment>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/templates" className="link">
                    Templates
                  </Link>
                </div>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/workouts" className="link">
                    Workouts
                  </Link>
                </div>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/journal" className="link">
                    Journal
                  </Link>
                </div>
                <div className="link-wrapper" onClick={handleClick}>
                  <Link to="/account" className="link">
                    Account
                  </Link>
                </div>
                <div className="link-wrapper" onClick={onLogout}>
                  <Link to="/" className="link">
                    Logout
                  </Link>
                </div>
              </React.Fragment>
            )}
          </Nav>
        </Navbar.Collapse>
      </Container>
    </Navbar>
  );
}
