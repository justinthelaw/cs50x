function handleCoverPhotoChange() {
  let jumbotron = document.getElementById("jumbotron");
  let url = document.getElementById("cover-photo-input").value;
  if (url.length > 0) {
    jumbotron.style["background-image"] = `url(${url})`;
    jumbotron.style["background-position"] = "center";

    let reverts = document.querySelectorAll(".revert");
    reverts.forEach((element) => {
      element.style.display = "";
    });
  }
  document.getElementById("cover-photo-input").value = "";
}

function handleRevert() {
  let url =
    "https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fwww.nitel.it%2Fwp-content%2Fuploads%2F2018%2F11%2Fearth-view-from-satellite-space-systems-cover.jpg&f=1&nofb=1";
  jumbotron.style["background-image"] = `url(${url})`;
  jumbotron.style["background-position"] = "";
  let reverts = document.querySelectorAll(".revert");
  reverts.forEach((element) => {
    element.style.display = "none";
  });
  document.getElementById("cover-photo-input").value = "";
}
