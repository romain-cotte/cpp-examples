"""=============================================================================
# Support Vector Machine

============================================================================="""


import timeit
from sklearn import svm
import mnist_loader


def svm_baseline():
    training_data, validation_data, test_data = mnist_loader.load_data()
    print("Data retrieved")

    clf = svm.SVC()
    # Train
    clf.fit(training_data[0], training_data[1])

    # Predict
    predictions = [int(a) for a in clf.predict(test_data[0])]
    num_correct = sum(int(a == y) for a, y in zip(predictions, test_data[1]))
    print("Baseline classifier using an SVM.")
    print("{0} of {1} values correct.".format(num_correct, len(test_data[1])))

if __name__ == "__main__":
    start = timeit.default_timer()
    svm_baseline()
    print("Execution time: {}s".format(timeit.default_timer() - start))


"""
Data retrieved
Baseline classifier using an SVM.
9785 of 10000 values correct.
Execution time: 214.87661682900216s
"""
