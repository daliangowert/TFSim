#include "correlation_predictor.hpp"

correlation_predictor::correlation_predictor(unsigned int t, unsigned int z, unsigned int g) : size_lin(t), n_bits(z), m_bits(g)
{
    max = (1 << n_bits) - 1;   // max = 3
    msb = (1 << (n_bits - 1)); // msb = 2
    state = 0;                 // pode ser tirado e colocado automaticamente na inicialização abaixo
    c_predictions = 0;
    c_hits = 0;
    size_col = 1 << m_bits;
    mask = (1 << m_bits) - 1;
    historic = 0;
    bp_buffer.resize(size_lin);
    for (auto &linha : bp_buffer)
    {
        linha.resize(size_col);
    }
}

bool correlation_predictor::cp_predict(unsigned int pc)
{
    c_predictions++;
    return (bp_buffer[pc % size_lin][historic] & msb);
}

void correlation_predictor::cp_update_state(unsigned int pc, bool taken, bool hit)
{
    int i = pc % size_lin;
    int state_aux = bp_buffer[i][historic];

    c_hits += hit;

    if (taken)
    {
        state_aux += (state_aux < max); // = ++state_aux>max?max:state_aux;
    }
    else
    {
        state_aux -= (state_aux > 0); // = --state_aux<0?0:state_aux;
    }

    bp_buffer[i][historic] = state_aux;

    // Atualiza historic
    historic = (historic << 1) | taken;
    historic &= mask;
}

float correlation_predictor::cp_get_hit_rate()
{
    return ((float)c_hits / (float)c_predictions) * 100;
}

std::array<int, 2> correlation_predictor::get_cp_size()
{
    std::array<int, 2> size;
    size[0] = m_bits;
    size[1] = n_bits;
    return size;
}

int correlation_predictor::cp_get_pred()
{
    return c_predictions;
}