export async function persist(setSession) {
  await fetch("/api/session")
    .then((res) => res.json())
    .then((data) => {
      setSession(data);
    });
}

export async function handleLogout(
  setSession,
  setShowAlert,
  setAlertType,
  setAlertMessage
) {
  await fetch("/api/logout")
    .then((res) => res.json())
    .then((data) => {
      if (data.error) {
        console.log(data.error);
      } else if (data.success) {
        setAlertType("success");
        setAlertMessage(data.success);
        setShowAlert(true);
        persist(setSession);
      } else {
        console.log("Something went wrong. Please try again.");
      }
    });
}
