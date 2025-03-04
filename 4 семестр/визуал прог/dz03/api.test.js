import { calcStatsFromAPI } from "./api.js";
import { loadData } from "./fetchData.js";
import { calcStats } from "./stats.js";

beforeEach(() => {
  jest.clearAllMocks();
});

jest.mock("./fetchData.js", () => ({
  loadData: jest.fn()
}));

jest.mock("./stats.js", () => ({
  calcStats: jest.fn()
}));

test("calcStatsFromAPI should return correct statistics", async () => {
  const mockData = [
    {
      breed: "Turkish Van",
      country: "developed in the United Kingdom (founding stock from Turkey)",
      origin: "Natural",
      coat: "Semi-long",
      pattern: "Van"
    },
    {
      breed: "York Chocolate",
      country: "United States (New York)",
      origin: "Natural",
      coat: "Long",
      pattern: "Solid"
    }
  ];

  loadData.mockResolvedValue(mockData);

  const mockStats = {
    "developed in the United Kingdom (founding stock from Turkey)": 1,
    "United States (New York)": 1
  };
  calcStats.mockReturnValue(mockStats);

  const result = await calcStatsFromAPI();

  expect(loadData).toHaveBeenCalledTimes(1);

  expect(calcStats).toHaveBeenCalledWith(mockData);

  expect(result).toEqual(mockStats);
});
