/* function that adds value of each data array  
 * of board b to all satistics objects
 */
void addToStats(int b)
{
  xs.add(x[b]); // add to acceleration statistics
  ys.add(y[b]);
  zs.add(z[b]);
  gs.add(g[b]); // add mG force statistics
  ps.add(p[b]); // add to pitch statistics
  rs.add(r[b]); // add to roll statistics
}
//----------------------------------------------------
/* function that clears the values of all
 * satistics objects
 */
void clearStats()
{
  xs.clear();
  ys.clear();
  zs.clear();
  gs.clear();
  ps.clear();
  rs.clear();
}
//----------------------------------------------------
/* function that calculates the means and the
 * standard deviations of all statistics objects
 */
void updateStats()
{
  /* means */
  xAv = xs.average();
  yAv = ys.average();
  zAv = zs.average();
  gAv = gs.average();
  pAv = ps.average();
  rAv = rs.average();
  /* standard deviations */
  xSD = xs.pop_stdev();
  ySD = ys.pop_stdev();
  zSD = zs.pop_stdev();
  gSD = gs.pop_stdev();
  pSD = ps.pop_stdev();
  rSD = rs.pop_stdev();
}
//----------------------------------------------------
/* function that finds the outlier based on the mean (av)
 * and standard deviation (sd) of data (z-score)
 */
int findOutlierSD(float* data, float av, float sd, double threshold)
{
  int outlier = nB;
  float current_max = 0;
  /* using z-score */
  if (sd < threshold) // necessary due to small population
    sd = 1.5;
  float z_score;
  for (int i = 0; i < nB; i++) {
    z_score = abs(data[i] - av)/sd;
    if (z_score > threshold && z_score > current_max) {
      outlier = i;
      current_max = z_score;
    }
  }
  return outlier;
}
//----------------------
/* based on the median absolute deviation (mad) of data
 * to calculate modified z-score.
 */
int findOutlierMAD(float* data, double threshold) {
  int outlier = nB;
  float current_max = 0;
  /* caclulate median of data */
  float s_data[nB]; // sorted data
  for (int i = 0; i < nB; i++) { 
    s_data[i] = data[i];
  }
  quickSort(s_data, 0, nB-1);
  float median = s_data[nB/2-1];
  /* calculate median absolute deviation */
  float s_md[nB];
  for (int i = 0; i < nB; i++) {
    s_md[i] = abs(data[i] - median);
  }
  quickSort(s_md, 0, nB-1);
  float mad = s_md[nB/2-1];
  /* using median absolute deviation */
  float z_score;
  for (int i = 0; i < nB; i++) {
    z_score = abs(data[i] - median)/mad;
    if (z_score > threshold && z_score > current_max) {
      outlier = i;
      current_max = z_score;
    }
  }
}
//----------------------
/* based on only the data deviation from mean */
int findOutlier(float* data, double threshold)
{
  int outlier = nB;
  float current_max = 0;
  /* using threshold of deviation */
  for (int i = 0; i < nB; i++) {
    if (data[i] > threshold && data[i] > current_max) {
      outlier = i;
      current_max = data[i];
    }
  }
  return outlier;
}

void quickSort(float arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
