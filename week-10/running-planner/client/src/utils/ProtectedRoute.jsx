// dependencies
import { useContext } from "react";
import AppContext from "../contexts/AppContext";
import Login from "../components/Login.jsx";

const ProtectedRoute = ({ component }) => {
  const { session } = useContext(AppContext);

  return session.auth ? component() : <Login forbidden />;
};

export default ProtectedRoute;
