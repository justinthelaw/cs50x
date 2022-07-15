export async function getConstants(page, setConstants) {
  await fetch(`/api/constants?page=${page}`)
    .then((res) => res.json())
    .then((data) => setConstants(data));
}
