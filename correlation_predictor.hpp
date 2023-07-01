#include <vector>
#include <array>
#include <iostream>

using namespace std;

class correlation_predictor {

public:
    correlation_predictor(unsigned int t, unsigned int z, unsigned int g);
    bool cp_predict(unsigned int pc);
    void cp_update_state(unsigned int pc, bool taken, bool hit);
    float cp_get_hit_rate();
    std::array<int, 2> get_cp_size();
    int cp_get_pred();

private:
    std::vector<std::vector<int>> bp_buffer;
    int size_lin, size_col, mask, n_bits, m_bits, max, msb, state, c_predictions, c_hits, historic;
};