def modify_to_grid_zero_fn(data):
    # mod_dataset2 = dataset2
    data.drop(['Grid'],axis=1) # Dropping the original grid with various grid numbers
    data['Grid'] = 0 # Replacing with new grid with 0
    return data

import matplotlib.pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
from sklearn import neighbors

def modify_to_grid_zero_fn(data):
    # mod_dataset2 = dataset2
    data.drop(['Grid'],axis=1) # Dropping the original grid with various grid numbers
    data['Grid'] = 0 # Replacing with new grid with 0
    return data

def get_knn_n_plot(X_train, X_test, y_train, y_test):
    # This will print the accuracy score for variou neigbour numbers
    allResults = []
    for kValue in range(1,50):
        knn = neighbors.KNeighborsClassifier(n_neighbors=kValue, metric="minkowski",p=1)
        knn = knn.fit(X_train,y_train)
        accuracy = knn.score(X_test, y_test)
        allResults.append(accuracy)
    plt.plot(allResults)
    plt.xlabel("Number of Neigbours")
    plt.ylabel("Accuracy Score")
    plt.title("KNN Accuracy Score for k Between 1 and 50")
    plt.show()
    plt.savefig('knn_num_of_n_plot.jpg')
    return allResults
