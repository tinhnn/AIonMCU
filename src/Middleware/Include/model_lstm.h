
#ifndef MODEL_BILSTM_H
#define MODEL_BILSTM_H


struct s_input {
  double data[12];
};

struct s_output {
  float data[12];
};


void model_init();
void model_deinit();
void predict(const s_input in[1], s_output out[1]);

#endif /* MODEL_BILSTM_H */
