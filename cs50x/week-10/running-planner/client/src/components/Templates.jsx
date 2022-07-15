// dependencies
import React from "react";

// components
import TemplateForm from "./TemplateForm.jsx";

// styles
import "../styles/Templates.css";

export default function Templates() {
  return (
    <div className="container templates">
      <div className="jumbotron-templates">
        <div className="py-1">
          <h1 className="display-6 fw-bold jumbo-text-templates">
            Template Builder
          </h1>
        </div>
      </div>
      <div className="form-area">
        <TemplateForm />
      </div>
    </div>
  );
}
