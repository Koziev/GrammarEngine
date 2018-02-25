// Accord Statistics Library
// Accord.NET framework
// http://www.crsouza.com
//
// Copyright © César Souza, 2009-2011
// cesarsouza at gmail.com
//

namespace Accord.Statistics.Models.Markov
{
    using System;
    using Accord.Math;

    /// <summary>
    ///   Hidden Markov Model Set for Sequence Classification.
    /// </summary>
    /// 
    /// <remarks>
    ///   This class uses a set of hidden Markov models to classify integer sequences.
    ///   Each model will try to learn and recognize each of the different output classes.
    /// </remarks>
    /// 
    /// <example>
    ///   <code>
    ///   // Declare some testing data
    ///   int[][] inputs =
    ///   {
    ///       new int[] { 0,1,1,0 },   // Class 0
    ///       new int[] { 0,0,1,0 },   // Class 0
    ///       new int[] { 0,1,1,1,0 }, // Class 0
    ///       new int[] { 0,1,0 },     // Class 0
    ///       
    ///       new int[] { 1,0,0,1 },   // Class 1
    ///       new int[] { 1,1,0,1 },   // Class 1
    ///       new int[] { 1,0,0,0,1 }, // Class 1
    ///       new int[] { 1,0,1 },     // Class 1
    ///   };
    ///     
    ///   int[] outputs =
    ///   {
    ///       0,0,0,0, // First four sequences are of class 0
    ///       1,1,1,1, // Last  four sequences are of class 1
    ///   };
    ///     
    ///   // We are trying to predict two different classes
    ///   int classes = 2;
    ///     
    ///   // Each sequence may have up to two symbols (0 or 1)
    ///   int symbols = 2;
    /// 
    ///   // Nested models will have two states each
    ///   int[] states = new int[] { 2, 2 };
    ///    
    ///   // Creates a new Hidden Markov Model Classifier with the given parameters
    ///   MarkovSequenceClassifier hmc = new MarkovSequenceClassifier(classes, symbols, states);
    ///     
    ///   // Will train until convergence of the average likelihood
    ///   double likelihood = hmc.Learn(inputs, outputs, 0.001);
    ///     
    ///   // And finally we will ask for the likelihood of a given sequence
    ///   hmc.Compute(inputs[i], out likelihood);
    ///   </code>
    /// </example>
    /// 
    [Serializable]
    public class MarkovSequenceClassifier
    {
        // Set of hidden Markov models
        private HiddenMarkovModel[] models;


        /// <summary>
        ///   Constructs a new Hidden Markov Model Sequence Classifier.
        /// </summary>
        public MarkovSequenceClassifier(int classes, int symbols, int[] states)
            : this(classes, symbols, states, null)
        {
        }

        /// <summary>
        ///   Constructs a new Hidden Markov Model Sequence Classifier.
        /// </summary>
        public MarkovSequenceClassifier(int classes, int symbols, int[] states, String[] names)
            : this(classes, symbols, states, names, HiddenMarkovModelType.Ergodic)
        {
        }

        /// <summary>
        ///   Constructs a new Hidden Markov Model Sequence Classifier.
        /// </summary>
        public MarkovSequenceClassifier(int classes, int symbols, int[] states, String[] names, HiddenMarkovModelType type)
        {
            models = new HiddenMarkovModel[classes];

            // For each of the possible output classes
            for (int i = 0; i < classes; i++)
            {
                // Create a Hidden Markov Models with the given number of symbols and states
                models[i] = new HiddenMarkovModel(symbols, states[i], type);

                if (names != null) models[i].Tag = names[i];
            }
        }

        /// <summary>
        ///   Gets the Hidden Markov Models contained in this ensemble.
        /// </summary>
        public HiddenMarkovModel[] Models
        {
            get { return models; }
        }

        /// <summary>
        ///   Trains each model to recognize each of the output labels.
        /// </summary>
        /// <returns>The sum log-likelihood for all models after training.</returns>
        public double Learn(int[][] inputs, int[] outputs, int iterations)
        {
            return Learn(inputs, outputs, iterations, 0);
        }

        /// <summary>
        ///   Trains each model to recognize each of the output labels.
        /// </summary>
        /// <returns>The sum log-likelihood for all models after training.</returns>
        public double Learn(int[][] inputs, int[] outputs, double tolerance)
        {
            return Learn(inputs, outputs, 0, tolerance);
        }

        /// <summary>
        ///   Trains each model to recognize each of the output labels.
        /// </summary>
        /// <returns>The sum log-likelihood for all models after training.</returns>
        public double Learn(int[][] inputs, int[] outputs, int iterations, double tolerance)
        {
            double sum = 0;

            // For each model,
            for (int i = 0; i < models.Length; i++)
            {
                // Select the input/output set corresponding
                //  to the model's specialization class
                int[] inx = outputs.Find(y => y == i);
                int[][] observations = inputs.Submatrix(inx);

                // Train the current model in the input/output subset
                sum += models[i].Learn(observations, iterations, tolerance);
            }

            // Returns the sum log-likelihood for all models.
            return sum;
        }

        /// <summary>
        ///   Computes the most likely class for a given sequence.
        /// </summary>
        public int Compute(int[] sequence, out double likelihood)
        {
            int label = 0;
            likelihood = 0.0;

            // For every model in the set,
            for (int i = 0; i < models.Length; i++)
            {
                // Evaluate the probability for the given sequence
                double p = models[i].Evaluate(sequence);

                // And select the one which produces the highest probability
                if (p > likelihood)
                {
                    label = i;
                    likelihood = p;
                }
            }

            // Returns the index of the most likely model.
            return label;
        }

        /// <summary>
        ///   Computes the most likely output for an array of input sequences.
        /// </summary>
        public int[] Compute(int[][] inputs, out double[] likelihood)
        {
            int[] outputs = new int[inputs.Length];
            likelihood = new double[inputs.Length];
            for (int i = 0; i < outputs.Length; i++)
                outputs[i] = Compute(inputs[i], out likelihood[i]);
            return outputs;
        }

    }
}
