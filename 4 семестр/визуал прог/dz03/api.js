import { loadData } from './fetchData.js';
import { calcStats } from './stats.js';

async function calcStatsFromAPI() {
  const cats = await loadData();
  return calcStats(cats);
}

calcStatsFromAPI()
    .then(stats => console.log(stats))
    .catch(error => console.error('Error:', error));

export { calcStatsFromAPI };
