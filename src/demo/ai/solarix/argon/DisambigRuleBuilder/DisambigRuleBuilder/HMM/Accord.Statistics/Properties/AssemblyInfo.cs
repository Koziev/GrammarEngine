#region Using directives

using System;
using System.Reflection;
using System.Runtime.InteropServices;

#endregion

// General Information about an assembly is controlled through the following 
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
[assembly: AssemblyTitle("Accord.Statistics")]
[assembly: AssemblyDescription("Accord.NET - Statistics Library")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("Accord.NET")]
[assembly: AssemblyProduct("Accord.Statistics")]
[assembly: AssemblyCopyright("Copyright © César Souza 2009-2011")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]
//[assembly: CLSCompliant(true)]

// This sets the default COM visibility of types in the assembly to invisible.
// If you need to expose a type to COM, use [ComVisible(true)] on that type.
[assembly: ComVisible(false)]

// The assembly version has following format :
//
// Major.Minor.Build.Revision
//
// You can specify all the values or you can use the default the Revision and 
// Build Numbers by using the '*' as shown below:
[assembly: AssemblyVersion("2.1.5.0")]
[assembly: AssemblyFileVersionAttribute("2.1.5.0")]


[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1020:AvoidNamespacesWithFewTypes", Scope = "namespace", Target = "Accord.Statistics")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1020:AvoidNamespacesWithFewTypes", Scope = "namespace", Target = "Accord.Statistics.Distributions")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1020:AvoidNamespacesWithFewTypes", Scope = "namespace", Target = "Accord.Statistics.Models.Markov")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1020:AvoidNamespacesWithFewTypes", Scope = "namespace", Target = "Accord.Statistics.Models.Regression")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1020:AvoidNamespacesWithFewTypes", Scope = "namespace", Target = "Accord.Statistics.Visualizations")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Statistics.Analysis.PartialLeastSquaresAnalysis.#nipals(System.Double[,],System.Double[,],System.Int32,System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Statistics.Analysis.PartialLeastSquaresAnalysis.#simpls(System.Double[,],System.Double[,],System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1809:AvoidExcessiveLocals", Scope = "member", Target = "Accord.Statistics.Analysis.PartialLeastSquaresAnalysis.#simpls(System.Double[,],System.Double[,],System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.Mixture`1.#Estimate(System.Double[],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.Mixture`1.#Estimate(System.Double[],System.Double,System.Double[],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.Mixture`1.#Estimate(System.Double[],System.Double[],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1500:VariableNamesShouldNotMatchFieldNames", MessageId = "mean", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.NormalDistribution.#Fit(System.Double[],System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1500:VariableNamesShouldNotMatchFieldNames", MessageId = "variance", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.NormalDistribution.#Fit(System.Double[],System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2233:OperationsShouldNotOverflow", MessageId = "x+1", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.PoissonDistribution.#DistributionFunction(System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Multivariate.Mixture`1.#Estimate(System.Double[][],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Multivariate.Mixture`1.#Estimate(System.Double[][],System.Double,System.Double[],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1000:DoNotDeclareStaticMembersOnGenericTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Multivariate.Mixture`1.#Estimate(System.Double[][],System.Double[],!0[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Multivariate.MultivariateContinuousDistribution.#Accord.Statistics.Distributions.IDistribution.ProbabilityFunction(System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Multivariate.MultivariateDiscreteDistribution.#Accord.Statistics.Distributions.IDistribution.ProbabilityFunction(System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.UnivariateDiscreteDistribution.#Accord.Statistics.Distributions.IDistribution.ProbabilityFunction(System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1710:IdentifiersShouldHaveCorrectSuffix", Scope = "type", Target = "Accord.Statistics.Filters.FiltersSequence")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Statistics.Models.Markov.ContinuousHiddenMarkovModel.#Learn(System.Array[],System.Int32,System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Statistics.Models.Markov.HiddenMarkovModel.#Learn(System.Int32[][],System.Int32,System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2233:OperationsShouldNotOverflow", MessageId = "inputs+1", Scope = "member", Target = "Accord.Statistics.Models.Regression.LogisticRegression.#.ctor(System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2233:OperationsShouldNotOverflow", MessageId = "inputs+1", Scope = "member", Target = "Accord.Statistics.Models.Regression.Linear.MultipleLinearRegression.#.ctor(System.Int32,System.Boolean)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2233:OperationsShouldNotOverflow", MessageId = "degree+1", Scope = "member", Target = "Accord.Statistics.Models.Regression.Linear.PolynomialRegression.#.ctor(System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes", Scope = "member", Target = "Accord.Statistics.Distributions.Univariate.UnivariateContinuousDistribution.#Accord.Statistics.Distributions.IDistribution.ProbabilityFunction(System.Double[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1034:NestedTypesShouldNotBeVisible", Scope = "type", Target = "Accord.Statistics.Filters.CodificationFilter+Options")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1034:NestedTypesShouldNotBeVisible", Scope = "type", Target = "Accord.Statistics.Filters.DiscretizationFilter+Options")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1034:NestedTypesShouldNotBeVisible", Scope = "type", Target = "Accord.Statistics.Filters.EqualizationFilter+Options")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1034:NestedTypesShouldNotBeVisible", Scope = "type", Target = "Accord.Statistics.Filters.LinearScalingFilter+Options")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1034:NestedTypesShouldNotBeVisible", Scope = "type", Target = "Accord.Statistics.Filters.NormalizationFilter+Options")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1724:TypeNamesShouldNotMatchNamespaces", Scope = "type", Target = "Accord.Statistics.Kernels.Linear")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "n", Scope = "member", Target = "Accord.Statistics.Tools.#Random(System.Int32,System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "k", Scope = "member", Target = "Accord.Statistics.Tools.#Random(System.Int32,System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1704:IdentifiersShouldBeSpelledCorrectly", MessageId = "n", Scope = "member", Target = "Accord.Statistics.Tools.#Random(System.Int32)")]

