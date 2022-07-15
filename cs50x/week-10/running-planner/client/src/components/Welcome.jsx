// dependencies
import React from "react";
import { Link } from "react-router-dom";

// hooks
import useWindowSize from "../hooks/useWindowSize.jsx";

// bootstrap
import { Button } from "react-bootstrap";
import { Box, Boxes, JournalBookmarkFill } from "react-bootstrap-icons";

// styles
import "../styles/Welcome.css";

export default function Welcome({ auth }) {
  const [width] = useWindowSize();

  const BUTTON_BREAK = width > 600;

  return (
    <div className="container-fluid jumbotron">
      <div className="p-4 jumbo-background rounded">
        <div className="container-fluid py-4">
          <h1 className="display-6 fw-bold jumbo-text">
            Welcome to <i>Running Planner</i>
          </h1>
          <p className="jumbo-subtext">
            {auth ? (
              "How can we help you with your running goals today?"
            ) : (
              <React.Fragment>
                Whether you are training to run your first mile or your
                hundredth marathon, <i>Running Planner</i> helps you plan,
                schedule, and track your workouts so that you can achieve your
                running goals.
              </React.Fragment>
            )}
          </p>
          {auth ? (
            <div className="buttons">
              <Link to="/templates" className="link flex-button">
                <Button variant="primary" size="lg">
                  <Box fontSize={25} />
                  {BUTTON_BREAK && <div className="button-break-large" />}
                  {BUTTON_BREAK && "Template Builder"}
                </Button>
              </Link>
              <Link to="/workouts" className="link flex-button">
                <Button variant="primary" size="lg">
                  <Boxes fontSize={25} />
                  {BUTTON_BREAK && <div className="button-break-large" />}
                  {BUTTON_BREAK && "Workout Planner"}
                </Button>
              </Link>
              <Link to="/journal" className="link flex-button">
                <Button variant="primary" size="lg">
                  <JournalBookmarkFill fontSize={25} />
                  {BUTTON_BREAK && <div className="button-break-large" />}
                  {BUTTON_BREAK && "Journal Entries"}
                </Button>
              </Link>
            </div>
          ) : (
            <div className="buttons unregistered-buttons">
              <Link to="/register" className="link flex-button">
                <Button variant="primary" size={BUTTON_BREAK ? "lg" : "md"}>
                  Get Started
                </Button>
              </Link>
              <Link to="/login" className="link flex-button">
                <Button variant="secondary" size={BUTTON_BREAK ? "lg" : "md"}>
                  Sign In
                </Button>
              </Link>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
