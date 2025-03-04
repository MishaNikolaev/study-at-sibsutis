import fetch from 'node-fetch';

async function loadData() {
  let url = "https://catfact.ninja/breeds";
  let dataUf = [];

  while (url) {
    const response = await fetch(url);
    const data = await response.json();
    dataUf = dataUf.concat(data.data);
    url = data.next_page_url;
  }
  return dataUf;
}

export { loadData };
