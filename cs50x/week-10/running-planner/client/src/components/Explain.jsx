// dependencies
import React from "react";

// styles
import "../styles/Explain.css";

export default function HowItWorks() {
  return (
    <div className="container-fluid jumbotron how-it-works">
      <div className="p-4 jumbo-background rounded">
        <div className="container-fluid py-4">
          <h1 className="display-6 fw-bold jumbo-text">How does it work?</h1>
          <p className="jumbo-subtext">
            <i>Running Planner</i> provides several building blocks that
            decrease the time you need to put into building your training plans
            and records while simultaneously improving their quality and
            useability.
          </p>
          <div className="container timeline-container">
            <div className="row">
              <div className="col">
                <div className="main-timeline">
                  <div className="timeline">
                    <div className="timeline-content">
                      <span className="timeline-title">Plan</span>
                      <div className="content">
                        <h3 className="title">Template Creation</h3>
                        <p className="description">
                          Fully-customizable, reusable, and shareable{" "}
                          <b>exercise templates</b> make it easy to create,
                          find, and add excercises to your workout routines.
                        </p>
                      </div>
                    </div>
                  </div>
                  <div className="timeline">
                    <div className="timeline-content">
                      <span className="timeline-title">Schedule</span>
                      <div className="content">
                        <h3 className="title">Calendar Events</h3>
                        <p className="description">
                          <b>Excercise templates</b> can be strung together to
                          create <b>workout routines</b>. These workout routines
                          can be exported as calendar event files to your
                          personal devices.
                        </p>
                      </div>
                    </div>
                  </div>
                  <div className="timeline">
                    <div className="timeline-content">
                      <span className="timeline-title">Track</span>
                      <div className="content">
                        <h3 className="title">Journaling</h3>
                        <p className="description">
                          As you create, share, and use templates, you can
                          record journal entries and track your progress inside
                          of your favorite <b>exercise templates</b> or{" "}
                          <b>workout routines</b>.
                        </p>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
