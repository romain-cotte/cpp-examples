"""=============================================================================
# Multi Layer Perceptron Classifier
============================================================================="""

import timeit
import mnist_loader
from sklearn.neural_network import MLPClassifier


def main():
    training_data, validation_data, test_data = mnist_loader.load_data()
    clf = MLPClassifier(
        solver='lbfgs',
        alpha=1e-4,
        hidden_layer_sizes=(30,),
        max_iter=1000,
        random_state=1,
        verbose=True
    )

    clf.fit(training_data[0], training_data[1])

    predictions = [int(a) for a in clf.predict(test_data[0])]
    num_correct = sum(int(a == y) for a, y in zip(predictions, test_data[1]))
    print("Baseline classifier using a mutli layer perceptron classifier.")
    print("{0} of {1} values correct.".format(num_correct, len(test_data[1])))


if __name__ == '__main__':
    start = timeit.default_timer()
    main()
    print("Execution time: {}s".format(timeit.default_timer() - start))



"""
/sklearn/neural_network/_multilayer_perceptron.py:545: ConvergenceWarning: lbfgs failed to converge (status=1):
STOP: TOTAL NO. of ITERATIONS REACHED LIMIT.

Increase the number of iterations (max_iter) or scale the data as shown in:
    https://scikit-learn.org/stable/modules/preprocessing.html
  self.n_iter_ = _check_optimize_result("lbfgs", opt_res, self.max_iter)
Baseline classifier using a mutli layer perceptron classifier.
9608 of 10000 values correct.
Execution time: 33.54024161000416s
"""
