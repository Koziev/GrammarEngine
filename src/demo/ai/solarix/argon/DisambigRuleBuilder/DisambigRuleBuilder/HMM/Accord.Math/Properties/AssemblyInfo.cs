#region Using directives

using System;
using System.Reflection;
using System.Runtime.InteropServices;

#endregion

// General Information about an assembly is controlled through the following 
// set of attributes. Change these attribute values to modify the information
// associated with an assembly.
[assembly: AssemblyTitle("Accord.Math")]
[assembly: AssemblyDescription("Accord.NET - Math Library")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("Accord.NET")]
[assembly: AssemblyProduct("Accord.Math")]
[assembly: AssemblyCopyright("Copyright © César Souza 2009-2011")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]

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


[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1719:ParameterNamesShouldNotMatchMemberNames", MessageId = "0#", Scope = "member", Target = "Accord.Math.Formats.MatrixFormatter.#Format(System.String,System.Array,Accord.Math.Formats.IMatrixFormatProvider)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Design", "CA1006:DoNotNestGenericTypesInMemberSignatures", Scope = "member", Target = "Accord.Math.Matrix.#CartesianProduct`1(System.Collections.Generic.IEnumerable`1<System.Collections.Generic.IEnumerable`1<!!0>>)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "FHT", Scope = "member", Target = "Accord.Math.HilbertTransform.#FHT(System.Double[],AForge.Math.FourierTransform+Direction)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "FHT", Scope = "member", Target = "Accord.Math.HilbertTransform.#FHT(AForge.Math.Complex[],AForge.Math.FourierTransform+Direction)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA1801:ReviewUnusedParameters", MessageId = "value", Scope = "member", Target = "Accord.Math.Matrix.#Equals(System.Object)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "Im", Scope = "member", Target = "Accord.Math.Matrix.#Im(AForge.Math.Complex[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "Re", Scope = "member", Target = "Accord.Math.Matrix.#Re(AForge.Math.Complex[])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "Sq", Scope = "member", Target = "Accord.Math.Special.#ChiSq(System.Double,System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "p", Scope = "member", Target = "Accord.Math.Special.#Log1p(System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "evl", Scope = "member", Target = "Accord.Math.Special.#P1evl(System.Double,System.Double[],System.Int32)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.EigenvalueDecomposition.#hqr2()")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1505:AvoidUnmaintainableCode", Scope = "member", Target = "Accord.Math.Decompositions.EigenvalueDecomposition.#hqr2()")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1500:VariableNamesShouldNotMatchFieldNames", MessageId = "n", Scope = "member", Target = "Accord.Math.Decompositions.EigenvalueDecomposition.#hqr2()")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzhes(System.Int32,System.Double[,],System.Double[,],System.Boolean,System.Double[,])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzit(System.Int32,System.Double[,],System.Double[,],System.Double,System.Boolean,System.Double[,],System.Int32&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1505:AvoidUnmaintainableCode", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzit(System.Int32,System.Double[,],System.Double[,],System.Double,System.Boolean,System.Double[,],System.Int32&)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzval(System.Int32,System.Double[,],System.Double[,],System.Double[],System.Double[],System.Double[],System.Boolean,System.Double[,])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1505:AvoidUnmaintainableCode", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzval(System.Int32,System.Double[,],System.Double[,],System.Double[],System.Double[],System.Double[],System.Boolean,System.Double[,])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.GeneralizedEigenvalueDecomposition.#qzvec(System.Int32,System.Double[,],System.Double[,],System.Double[],System.Double[],System.Double[],System.Double[,])")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "Lu", Scope = "type", Target = "Accord.Math.Decompositions.LuDecomposition")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.NonnegativeFactorization.#init(System.Double[,],System.Int32,Accord.Math.Decompositions.NonnegativeFactorizationAlgorithm,System.Double[,],System.Double[,],System.Int32,System.Int32,System.Double,System.Double)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Naming", "CA1709:IdentifiersShouldBeCasedCorrectly", MessageId = "Qr", Scope = "type", Target = "Accord.Math.Decompositions.QrDecomposition")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity", Scope = "member", Target = "Accord.Math.Decompositions.SingularValueDecomposition.#.ctor(System.Double[,],System.Boolean,System.Boolean,System.Boolean)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Performance", "CA1809:AvoidExcessiveLocals", Scope = "member", Target = "Accord.Math.Decompositions.SingularValueDecomposition.#.ctor(System.Double[,],System.Boolean,System.Boolean,System.Boolean)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1505:AvoidUnmaintainableCode", Scope = "member", Target = "Accord.Math.Decompositions.SingularValueDecomposition.#.ctor(System.Double[,],System.Boolean,System.Boolean,System.Boolean)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.DefaultMatrixFormatProvider.#InvariantCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.DefaultMatrixFormatProvider.#CurrentCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.CSharpMatrixFormatProvider.#InvariantCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.CSharpMatrixFormatProvider.#CurrentCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.CSharpJaggedMatrixFormatProvider.#InvariantCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.CSharpJaggedMatrixFormatProvider.#CurrentCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.OctaveMatrixFormatProvider.#CurrentCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Security", "CA2104:DoNotDeclareReadOnlyMutableReferenceTypes", Scope = "member", Target = "Accord.Math.Formats.OctaveMatrixFormatProvider.#InvariantCulture")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Globalization", "CA1305:SpecifyIFormatProvider", MessageId = "System.String.Format(System.String,System.Object)", Scope = "member", Target = "Accord.Math.Formats.MatrixFormatter.#Format(System.String,System.Array,Accord.Math.Formats.IMatrixFormatProvider)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Globalization", "CA1305:SpecifyIFormatProvider", MessageId = "System.String.Format(System.String,System.Object)", Scope = "member", Target = "Accord.Math.Formats.MatrixFormatter.#handleOtherFormats(System.String,System.Object,System.Globalization.CultureInfo)")]
[assembly: System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Maintainability", "CA1500:VariableNamesShouldNotMatchFieldNames", MessageId = "k", Scope = "member", Target = "Accord.Math.Decompositions.NonnegativeFactorization.#init(System.Double[,],System.Int32,Accord.Math.Decompositions.NonnegativeFactorizationAlgorithm,System.Double[,],System.Double[,],System.Int32,System.Int32,System.Double,System.Double)")]

