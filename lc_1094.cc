class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int min_location_idx = INT_MAX, max_location_idx = INT_MIN;
        for (const auto& trip : trips) {
            min_location_idx = min(min_location_idx, trip[1]);
            max_location_idx = max(max_location_idx, trip[2]);
        }
        vector<int> trip_marks(max_location_idx - min_location_idx + 1, 0);
        vector<int> passengers(max_location_idx - min_location_idx + 1, 0);
        for (const auto& trip : trips) {
            trip_marks[trip[1] - min_location_idx] += trip[0];
            if (trip[2] - min_location_idx < int(trip_marks.size())) {
                trip_marks[trip[2] - min_location_idx] -= trip[0];
            }
        }
        
        std::partial_sum(trip_marks.begin(), trip_marks.end(), passengers.begin());
        return not std::any_of(passengers.begin(), passengers.end(), 
            [capacity](int num_passengers) { return num_passengers > capacity; });
    }
};
