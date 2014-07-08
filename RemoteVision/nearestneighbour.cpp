/*
 * File:   NearestNeighbour.cpp
 * Author: Dennis Ideler <di07ty at brocku.ca>
 *
 * Created on May 2012
 *
 */

#include "nearestneighbour.h"
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <cstring>
#include <cstdlib>


using namespace std;

NearestNeighbour::NearestNeighbour(const int k, const int num_attributes) //k = 7 408 attributes
    : k_(k), num_attributes_(num_attributes) {}

NearestNeighbour::~NearestNeighbour()
{
  // check if any heap allocated memory is not null
  // then delete it
}

/**
 * Performs the lazy learning phase of kNN.
 * Unweighted k-nearest neighbour for classification.
 * Finds the k closest instances and takes the majority class.
 *
 * @param training_set The set of labeled examples to compare against.
 * @param testing_set The set of "unlabeled" examples to test accuracy.
 * @param verbose Boolean for outputting extra classification information.
 * @return The classification accuracy.
 */
double NearestNeighbour::learn(const char* filename,
                             const char* image,
                             const bool verbose) const
{
    ifstream training_set(filename);
    ifstream testing_set(image);

    string line = "";
    getline(testing_set, line);

    char* imge = new char[line.length() + 1];
    strcpy(imge, line.c_str());

    //tokenize
    char* pch;

    pch = strtok(imge, ", ");
    vector<float> img;
    while( pch != NULL)
    {
        img.push_back(atof(pch));
        pch = strtok(NULL, ", ");
    }

    delete [] imge;

    vector< vector< float > > db;

    line = "";
    while(getline(training_set, line))
    {
        vector<float> ex;
        char* example = new char[line.length() + 1];
        strcpy(example, line.c_str());

        pch = strtok(example, ", ");

        while(pch != NULL)
        {
            ex.push_back(atof(pch));
            pch = strtok(NULL, ", ");
        }
        db.push_back(ex);

        delete [] example;
    }

  // For each unclassified example (ie instance in testing set),
  int total_hits = 0;
  int total_cases = 1;
  int target = img[num_attributes_];
  int ret = 0;
  //int total_cases = testing_set.size();
  for (int i = 0; i < total_cases; ++i)
  {
    int classification = computeNearestNeighbours(img, db);
    //int target = testing_set[i][num_attributes_];

    //if (classification == target) ++total_hits;

    if (verbose)
    {
      cout //<< "Expected outcome: " << target
           << "Actual outcome: " << classification << "\n\n";
    }
    ret = classification;
  }

  double accuracy = (static_cast<float>(total_hits) / total_cases) * 100;
  //cout << "Correctly classified " << total_hits << " out of " << total_cases
       //<< " = " << accuracy << "%\n\n";
  return ret;
}

/**
 * Computes the distance to each classified example.
 * Sorts the distances and chooses the k nearest.
 * Returns the majority vote of the k nearest neighbours.
 *
 * @param query The unclassified example.
 * @param training_set The dataset to compare against.
 * @return The predicted classification of the query.
 */
int NearestNeighbour::computeNearestNeighbours(
    const vector<float> query,
    const vector< vector<float> > training_set) const
{
  int size = training_set.size();

  //DEBUG
  //cout << "Training_Set size = " << size << endl;
  vector<neighbour> neighbours;
  for (int i = 0; i < size; ++i)
  {
    //DEBUG
      if(query.size() != training_set[i].size() - 1)
      {
          cout << "Query Size = " << query.size() << '\t' << "Training_set[" << i << "] Size = " << training_set[i].size() << endl;
      }
    neighbour n;
    n.distance = distR(query, training_set[i]); // dist() not being used atm.
    n.classification = training_set[i][num_attributes_];
    neighbours.push_back(n);
  }

  sort(neighbours.begin(), neighbours.end());

  // Tally up the votes from the k nearest neighbours.
  map<int, int> votes;
  set<int> classes;
  for (int i = 0; i < k_; ++i)
  {
//    cout << "neighbour " << i+1 << ":  " << neighbours[i].classification
//         << " " << neighbours[i].distance << "\n";
    votes[neighbours[i].classification]++;
    classes.insert(neighbours[i].classification);
  }

  // Determine which class has the highest vote.
  set<int>::iterator it;
  int majority_vote = -99999999;
  int majority_class = -1;
  for (it = classes.begin(); it != classes.end(); ++it)
  {
    int classification = *it;
    if (votes[classification] > majority_vote)
    {
      majority_vote = votes[classification];
      majority_class = classification;
    }
  }
  return majority_class;
}


/**
 * Euclidean distance metric.
 *
 * @param query The unclassified example.
 * @param record The classified example.
 * @return The distance between the two examples.
 */
double NearestNeighbour::dist(const vector<float> query,
                              const vector<float> record) const
{
  assert(query.size() == record.size());
  double temp = 0;
  for (int i = 0; i < static_cast<int>(query.size()); ++i)
  {
    temp += sqr(query[i] - record[i]);
  }
  return sqrt(temp);
}

/**
 * Euclidean squared distance metric. More efficient than the actual distance.
 * Use when you need distance for comparisons, not the actual distance.
 *
 * @param query The unclassified example.
 * @param record The classified example.
 * @return The squared "distance" between the two examples.
 */
double NearestNeighbour::distR(const vector<float> query,
                               const vector<float> record) const
{
  assert(query.size() == record.size() - 1);
  double temp = 0;
  for (int i = 0; i < static_cast<int>(query.size() - 1); ++i)
  {
    temp += sqr(query[i] - record[i]);
  }
  return temp;
}

/**
 * A generic function to square a value.
 */
template<class T> inline T NearestNeighbour::sqr(const T &x) const
{
  return x * x;
}
