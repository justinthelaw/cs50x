// dependencies
import React, { useState, useEffect, useContext } from "react";
import AppContext from "../contexts/AppContext";
import { getConstants } from "../utils/constants.js";
import { handlePost } from "../utils/fetch.js";

// bootstrap
import { Form, Button, Row, Col } from "react-bootstrap";

export default function Templates() {
  const { setShowAlert, setAlertMessage, setAlertType } =
    useContext(AppContext);

  const [constants, setConstants] = useState(null);
  const [title, setTitle] = useState("");
  const [validTitle, setValidTitle] = useState(true);
  const [url, setURL] = useState("");
  const [validURL, setValidURL] = useState(true);
  const [description, setDescription] = useState("");
  const [validDescription, setValidDescription] = useState(true);
  const [amount, setAmount] = useState(0);
  const [validAmount, setValidAmount] = useState(true);
  const [units, setUnits] = useState("");
  const [validUnits, setValidUnits] = useState(true);

  useEffect(() => {
    getConstants("templates", setConstants);
  }, []);

  useEffect(() => {
    setUnits(constants?.VALID_UNITS[0]);
  }, [constants?.VALID_UNITS]);

  const handleSubmit = (event) => {
    event.preventDefault();
    const data = {
      title: title,
      url: url,
      description: description,
      amount: amount,
      units: units,
    };
    handlePost(
      data,
      "/api/templates",
      setAlertMessage,
      setAlertType,
      setShowAlert
      // callback
    );
  };

  const validForm = () =>
    title &&
    description &&
    amount &&
    validTitle &&
    validURL &&
    validDescription &&
    validAmount &&
    validUnits;

  const validateTitle = (title) =>
    title.length >= constants.TITLE_MIN && title.length <= constants.TITLE_MAX
      ? setValidTitle(true)
      : setValidTitle(false);

  const validateURL = (url) =>
    url.length >= constants.URL_MIN && url.length <= constants.URL_MAX
      ? setValidURL(true)
      : setValidURL(true);

  const validateDescription = (description) =>
    description.length >= constants.DESC_MIN &&
    description.length <= constants.DESC_MAX
      ? setValidDescription(true)
      : setValidDescription(false);

  const validateAmount = (amount) => {
    amount.length >= constants.AMOUNT_MIN &&
    amount.length <= constants.AMOUNT_MAX
      ? setValidAmount(true)
      : setValidAmount(false);
  };

  const validateUnits = (units) =>
    constants.VALID_UNITS.includes(units)
      ? setValidUnits(true)
      : setValidUnits(false);

  return constants ? (
    <div className="template-form">
      <Form onSubmit={handleSubmit}>
        <Form.Group className="input" size="lg" controlId="title">
          <Form.Label>Name</Form.Label>
          <Form.Control
            autoFocus
            required
            placeholder="Exercise name"
            type="text"
            value={title}
            isInvalid={!validTitle}
            onChange={(e) => {
              setTitle(e.target.value);
              validateTitle(e.target.value);
            }}
          />
          {validTitle && (
            <Form.Text>
              {title.length} / {constants.TITLE_MAX}
            </Form.Text>
          )}
          <Form.Control.Feedback type="invalid">
            {title.length} / {constants.TITLE_MAX}
          </Form.Control.Feedback>
        </Form.Group>
        <Form.Group className="input" size="lg" controlId="url">
          <Form.Label>URL</Form.Label>
          <Form.Control
            placeholder="Optional link to images or videos"
            type="url"
            value={url}
            isInvalid={!validURL}
            onChange={(e) => {
              setURL(e.target.value);
              validateURL(e.target.value);
            }}
          />
          {validURL && (
            <Form.Text>
              {url.length} / {constants.URL_MAX}
            </Form.Text>
          )}
          <Form.Control.Feedback type="invalid">
            {url.length} / {constants.URL_MAX}
          </Form.Control.Feedback>
        </Form.Group>
        <Form.Group
          className="input textarea"
          size="lg"
          controlId="description"
        >
          <Form.Label>Description</Form.Label>
          <Form.Control
            required
            placeholder="How is the exercise performed?"
            as="textarea"
            rows={5}
            value={description}
            isInvalid={!validDescription}
            onChange={(e) => {
              setDescription(e.target.value);
              validateDescription(e.target.value);
            }}
          />
          {validDescription && (
            <Form.Text>
              {description.length} / {constants.DESC_MAX}
            </Form.Text>
          )}
          <Form.Control.Feedback type="invalid">
            {description.length} / {constants.DESC_MAX}
          </Form.Control.Feedback>
        </Form.Group>
        <Row className="align-items-center">
          <Col sm={4}>
            <Form.Group className="input" size="lg" controlId="unit">
              <Form.Label>Units</Form.Label>
              <Form.Select
                required
                as="select"
                value={units}
                isInvalid={!validUnits}
                onChange={(e) => {
                  setUnits(e.target.value);
                  validateUnits(e.target.value);
                }}
              >
                {constants.VALID_UNITS.map((unit, index) => {
                  return (
                    <option key={index} value={unit}>
                      {unit}
                    </option>
                  );
                })}
              </Form.Select>
              {validUnits && <Form.Text>Select Units</Form.Text>}
              <Form.Control.Feedback type="invalid">
                Invalid Selection
              </Form.Control.Feedback>
            </Form.Group>
          </Col>
          <Col sm={8}>
            <Form.Group className="input" size="lg" controlId="amount">
              <Form.Label>Amount</Form.Label>
              <Form.Control
                required
                placeholder="Amount"
                type="number"
                value={amount}
                isInvalid={!validAmount}
                onChange={async (e) => {
                  setAmount(e.target.value);
                  validateAmount(e.target.value);
                }}
              />
              {validAmount && <Form.Text>Time or Repititions</Form.Text>}
              <Form.Control.Feedback type="invalid">
                Invalid Amount
              </Form.Control.Feedback>
            </Form.Group>
          </Col>
        </Row>
        <Button
          className="button"
          size="md"
          type="submit"
          disabled={!validForm()}
        >
          Save Template
        </Button>
      </Form>
    </div>
  ) : (
    <div className="templates d-flex justify-content-center">
      <div className="spinner-border" role="status" />
    </div>
  );
}
