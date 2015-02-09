#include "cnn/param-edges.h"

#include <sstream>

using namespace std;

namespace cnn {

bool ParameterEdge::has_parameters() const { return true; }

string ParameterEdge::as_string(const vector<string>& arg_names) const {
  ostringstream s;
  s << "params" << dim;
  return s.str();
}

Matrix ParameterEdge::forward(const vector<const Matrix*>& xs) const {
  assert(xs.size() == 0);
  return params->values;
}

Matrix ParameterEdge::backward(const vector<const Matrix*>& xs,
                    const Matrix& fx,
                    const Matrix& dEdf,
                    unsigned i) const {
  cerr << "called backward() on arity 0 edge\n";
  abort();
}

void ParameterEdge::accumulate_grad(const Matrix& g) {
  params->accumulate_grad(g);
}

string InputEdge::as_string(const vector<string>& arg_names) const {
  ostringstream s;
  s << "inputs" << dim;
  return s.str();
}

Matrix InputEdge::forward(const vector<const Matrix*>& xs) const {
  assert(xs.size() == 0);
  return params->values;
}

Matrix InputEdge::backward(const vector<const Matrix*>& xs,
                    const Matrix& fx,
                    const Matrix& dEdf,
                    unsigned i) const {
  cerr << "called backward() on arity 0 edge\n";
  abort();
}

void InputEdge::accumulate_grad(const Matrix& g) {
  cerr << "called accumulate_grad() on InputEdge\n";
  abort();
}

string LookupEdge::as_string(const vector<string>& arg_names) const {
  ostringstream s;
  s << "lookup[|x|=" << params->values.size() << " --> " << dim << ']';
  return s.str();
}

Matrix LookupEdge::forward(const vector<const Matrix*>& xs) const {
  assert(xs.size() == 0);
  return params->embedding();
}

Matrix LookupEdge::backward(const vector<const Matrix*>& xs,
                            const Matrix& fx,
                            const Matrix& dEdf,
                            unsigned i) const {
  cerr << "called backward() on arity 0 edge\n";
  abort();
}

void LookupEdge::accumulate_grad(const Matrix& g) {
  params->accumulate_grad(g);
}

} // namespace cnn