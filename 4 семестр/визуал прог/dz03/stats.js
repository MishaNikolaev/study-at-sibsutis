function calcStats(catsInfo) {
  return catsInfo.reduce((acc, cat) => {
    acc[cat.country] = (acc[cat.country] || 0) + 1;
    return acc;
  }, {});
}

export { calcStats };
