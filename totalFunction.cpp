vector<vector<vector<int>>> totalCost(vector<vector<vector<int>>> cost, Mat right, Mat left, int D, int W) {
	Mat rightGray, leftGray;
	vector<vector<vector<int>>> total;
	int C, sum = 0;
	cvtColor(right, rightGray, CV_BGR2GRAY);
	cvtColor(left, leftGray, CV_BGR2GRAY);

	for (int x = 0; x < rightGray.rows; x++) {
		total.resize(total.size() + 1);
		for (int y = 0; y < rightGray.cols; y++) {
			total[x].resize(total[x].size() + 1);
			for (int d = 0; d < D; d++) {
				sum = 0;
				if (x - d < 0)
					break;
				for (int i = -1 * W / 2; i <= W / 2; i++) {
					for (int j = -1 * W / 2; j <= W / 2; j++) {
						if (x + i - d < 0 || x + i < 0 || y + j < 0 || x + i > cost.size() - 1 || y + j > cost[0].size() - 1)
							continue;
						sum += cost[x + i][y + j][d];
					}
				}
				total[x][y].push_back(sum);
			}
		}
	}

	return total;
}