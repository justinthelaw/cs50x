export async function handlePost(
  data,
  endpoint,
  setMessage,
  setType,
  setShow,
  callback
) {
  await fetch(endpoint, {
    credentials: "include",
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
  })
    .then((res) => res.json())
    .then((data) => {
      if (data.error) {
        console.log(data.error);
        setMessage(data.error);
        setType("danger");
      } else if (data.success) {
        setMessage(data.success);
        setType("success");
        if (callback) callback();
      } else {
        console.log("Something went wrong. Please try again.");
        setMessage("Something went wrong. Please try again.");
        setType("danger");
      }
    })
    .then(() => setShow(true));
}
