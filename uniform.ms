.\"$Id: uniform.ms,v 3.27 2002-01-06 16:29:02+02 rl Exp $
.if !c\(sr .char \(sr sqrt
.if !c\(!= .char \(!= !=
.if !c\(*a .char \(*a alpha
.if !c\(*g .char \(*g gamma
.if !c\(*p .char \(*p pi
.if !c\(*h .char \(*h theta
.if !c\(*r .char \(*r rho
.if !c\(*f .char \(*f phi
.if !c\(*S .char \(*S sum
.if !c\(*d .char \(*d delta
.if !c\(*t .char \(*t tau
.if !c\(*x .char \(*x chi
.if !c\(sc .char \(sc Section \"
.AM
.EQ
delim $$
define / 'over'
define @ 'size -2'
define 3#2 '@{3 / 2}'
define 4#3 '@{4 / 3}'
define 5#2 '@{5 / 2}'
define 5#3 '@{5 / 3}'
define 5#4 '@{5 / 4}'
define 6#5 '@{6 / 5}'
define 8#3 '@{8 / 3}'
define 8#5 '@{8 / 5}'
define 8#7 '@{8 / 7}'
define 10#3 '@{10 / 3}'
define 10#7 '@{10 / 7}'
define 10#9 '@{10 / 9}'
define pi#2 '@{pi / 2}'
define pi#4 '@{pi / 4}'
define 3pi#4 '@{{3 pi} / 4}'
.EN
.TL
Uniform Solution for Uniform Polyhedra*
.FS *
In memoriam of my father, Gershon Har'El,
who introduced me to spatial structures.
.FE
.FS
.I "Geometriae Dedicata"
.B 47:
57-110, 1993.
.FE
.AU
Zvi Har'El
.AI
Department of Mathematics
Technion \- Israel Institute of Technology
Haifa 32000, Israel
E-Mail: rl@math.technion.ac.il
.AB
An arbitrary precision solution of uniform polyhedra and their duals is
presented. The solution is uniform for all polyhedra given by their
kaleidoscopic construction, with no need to `examine' each polyhedron
separately.
.AE
.NH
Introduction.
.PP
Uniform polyhedra, whose faces are regular and vertices equivalent, have
been studied since antiquity. Best known are the five Platonic solids and the
13 Archimedean solids. We then have the two infinite families of uniform
prisms and antiprisms. Allowing for star faces or vertices, we have the four
Kepler-Poinsot regular star polyhedra and a row of 53 nonconvex
uniform polyhedra discovered in the 1880s and the 1930s.
The complete set appeared in print for the first time in 1953, in a paper by
Coxeter, Longuet-Higgins and Miller ([CLM], see also [S]).
.PP
Magnus Wenninger's delightful book
.I "Polyhedron Models"
[W1],
which appeared in 1971 but since has been reprinted many times, contains
photos and building instructions for cardboard models of these 75
uniform polyhedra. Reading the book, makes the mathematically minded reader
wonder: How are the data for the models obtained? For example, what makes
$1.1600030093$ the proper circumradius for a
.I "great retrosnub icosidodecahedron" \**
.FS
This is the [W2] version of the polyhedron name.
.FE
with edge length two?
.PP
It is easy to check, that these data originate in [CLM, Table 7].
Some of the circumradii are exact, as they are given in terms of
integers and radicals only, but few, as the one mentioned above,
are given approximately, to ten decimal digits.
This may be considered perhaps accurate enough, but if one
wants to incorporate polyhedra in a computer modeling software (cf. [Hy]),
one would prefer to get the numbers in an arbitrary precision, or in
the maximum precision the computer can handle.
Furthermore, one is interested in exact, or maximum precision, values
of other geometric data, such as the dihedral angles of the polyhedra, and for
these the only available data are for the regular and the convex cases, and are
accurate to $1 prime prime$ (cf. [CR, Table II] and [J, Table II]).
.PP
This problem was treated by Andrew Hume. His method is best described
by a short quotation from his report [Hm]:
.QP
.I
In general, the data are solutions of equations found by examining
the polyhedra (for example [L, pp. 174-176]). The equations were solved at least
three times using symbolic algebra systems...
.R
.PP
Uniform polyhedra for which symbolic algebra systems are useful
are the so-called snub polyhedra,
and the computations involve solving cubic or quartic equations.
Hume's solutions were used to create a database of polyhedra, which is
publicly available at
.I netlib@research.att.com .
.PP
Our approach is quite different. Rather then separately examining
individual polyhedra, we suggest a uniform approach, which is easy to
understand and easy to use, even with a hand-held calculator, and it eliminates
the need for a database for uniform polyhedra and their duals, since the
fast iterative algorithm may yield arbitrary precision data. Furthermore, it
may be used in the same ease for convex as well as for nonconvex polyhedra
(which are not treated by [Hm]). A computer program, called
.I kaleido
(cf. [Ha]) and publicly available at
.I ftp@ftp.math.technion.ac.il ,
has been developed to
compute the data of a uniform polyhedron (and its dual), given either the
vertex configuration, i.e, the enumeration of the polygons appearing as faces
incident at a vertex in the order in which they are found (cf.
[CR, \(sc2.9.2]), or the so-called
.I "Wythoff symbol"
which describes the kaleidoscopic construction of the polyhedron (cf.
[CLM, \(sc3]).
.I Kaleido
is also capable of computing the vertex and face coordinates
and displaying a rotating wire-frame image of each polyhedron.
.PP
We would like to express our gratitude to H. S. M. Coxeter,
Branko Gru\*:nbaum and Andrew Hume,
for the very useful and enlightening comments.
.NH
The Fundamental System.
.PP
The
.I "uniform solution"
is based upon projecting the uniform polyhedron onto a concentric sphere,
decomposing each $n$-sided tile in the spherical tiling into $2n$
congruent right-angled spherical triangles,
setting the trigonometric equations and solving them iteratively.
We shall explain the solution algorithm in the next section.
Here, we discuss the procedure of identifying the fundamental triangles
and setting the fundamental equations.
.PP
Let us assume, for the moment, that we are investigating a convex
uniform polyhedron, such that each of its vertices is incident to $m$ faces,
with the $i$th face being a regular $n sub i$-gon, customarily denoted by
the
.I "Schla\*:fli symbol"
{$n sub i$}.
The cyclic list $(n sub 1 . n sub 2 . ... . n sub m )$ is the
.I "vertex configuration" .
.PP
Projecting the polyhedron on a concentric sphere, we get a spherical
tiling.
Choose a vertex $C$, and let $A sub i$, for $i=1, ... ,m$, be the
incenter of the of the $i$th tile incident to $C$.
Also, let $B sub i$ be the foot of the perpendicular from $A sub i$
to the arc separating the $i$th and $(i+1)$st tiles
(the $(m+1)$st being identified as the first). In fact, the spherical polygon
$A sub 1 A sub 2 ... A sub m$ is the
.I "prototile"
of the
.I "dual tiling"
(cf. [GS, \(sc1.2]).
Also, the planar polygon $B sub 1 B sub 2 ... B sub m$ is the so called
.I "vertex figure"
at $C$ (cf. [C, \(sc2.1]).
.PP
This way, we decompose the spherical tiling into right-angled spherical triangles,
called the
.I "fundamental triangles" :
At each vertex $C$ we get $2m$
fundamental triangles, arranged in congruent pairs
$A sub i B sub i-1 C$ and $A sub i B sub i C$, for $i=1, ... ,m$.
The set of fundamental triangles will be called the
.I "fundamental triangulation" .
Note that the same triangulation also arise from a similar decomposition of the
dual tiling (cf. [GS], section 2.7).
.PP
Denote the sides and the angles of $A sub i B sub i C$ by
$a sub i$, $b sub i$, $c sub i$, $alpha sub i$, $pi#2$, $gamma sub i$,
in the obvious manner (the right angle is at $B sub i$).
From the definition of $A sub i$, and the regularity of the face, we easily see
.EQ (1)
n sub i alpha sub i = pi ,
.EN
for $i=1, ... ,m$.
Furthermore, if we consider the angles of the fundamental triangles meeting
at $C$, we get
.EQ (2)
sum gamma sub i = pi .
.EN
Finally, we use the fact that the edge $C B sub i$ is shared by the two
neighboring fundamental triangles $A sub i B sub i C$ and
$A sub i+1 B sub i C$, and get $a sub i = a sub i+1$.
Thus, all the $a sub i$'s are equal, and the common value, say $a$, satisfies
.EQ (3)
cos a = {cos alpha sub i} / {sin gamma sub i}
.EN
for $i=1, ... ,m$,
as may be easily deduced from the spherical law of cosines, or from
Napier's second rule of circular parts (cf. [M]).
.PP
Thus, we get a system of $2m+1$ simultaneous equations (where $m+1$ are
linear and $m$ are trigonometric) in the $2m+1$
unknowns $alpha sub i$, $gamma sub i$ and $cos a$.
We name it the
.I "fundamental system" ,
and we shall describe its solution in the next section.
.PP
Once the fundamental system has been solved, the rest of the sides of
the fundamental triangles may be solved using similar formulas:
.EQ
cos c sub i = {cos gamma sub i} / {sin alpha sub i}
.EN
.EQ
cos b sub i = 1 / {tan alpha sub i tan gamma sub i}
.EN
.PP
The solution of the fundamental triangles reflects directly on the problem
of finding all the metrical properties of the uniform polyhedron: Let
$R, rho ,r sub i ,l,h sub i , theta sub i , phi sub i$, be
respectively the circumradius (the distance from the center to a vertex),
the midradius (the distance from the center to an edge), the inradius
(the distance from the center to the face), the semiedge, the facial inradius,
the facial angle and the dihedral angle (the angle between the the $i$'th
and the $i+1$'st faces). Then it is not hard to verify that
$rho / R = cos a$,
$r sub i / rho = cos c sub i$,
$l / rho = tan a$,
$h sub i / r sub i = tan c sub i$,
$theta sub i = pi -2 alpha sub i$,
$phi sub i = pi -c sub i -c sub i+1$.
.PP
The construction described above can be easily adjusted to accommodate
nonconvex uniform polyhedra\**.
.FS
The corresponding spherical tiling consists of
.I "hollow tiles"
in the sense of [GMS] (cf. [GS], section 12.3),
and the fundamental triangulation be viewed as a multiple tiling of the sphere
by triangles, or a triangulation of a Riemann surface
(cf. [GS], section 12.4)).
.FE
Such polyhedra may have star polygons as faces, or
have the faces meeting at a vertex surround it more than once.
In the former case $n sub i$ may be taken fractional (with the denominator
being the
.I density
of the star face, cf. [C]),
and in the latter case the right hand side of (2) is a multiple of $pi$
(with the multiplier being the density of the star vertex).
Finally, nonconvex polyhedra may have
.I retrograde
faces, as follows:
Choose an arbitrary orientation on the circumcircle of the vertex figure.
The $i$'th face is said to be retrograde if the shorter of the the two arcs
connecting $B sub i-1$ to $B sub i$ is oppositely oriented.
(We assume that at least one face is not retrograde!)
In this case we will represent a retrograde
{$n$} by an {$n prime$}, with $n prime <2$ satisfying
$1 / n + 1 / {n prime} =1$. This will make $alpha prime = pi - alpha$
obtuse, and $gamma prime =- gamma$ negative, as required.
We will reiterate on these adjustments in the next section.
.PP
It is worthwhile to note that [CLM], p. 420, utilize the circumcircle of
the vertex figure and elementary plane trigonometry to derive a set of equations
which is essentially identical to our fundamental system. They are also
able to obtain, by elimination, a single quartic equation, and use it to
to prove that their list of snub polyhedra is complete (cf. [CLM], table 4).
However, from our point of view, such derivation obscures the tight relationship
between uniform polyhedra and their fundamental triangulations, a 
relationship which will be instrumental in section 4. Furthermore, the
elimination method is not as uniform as the iterative solution to be presented
in section 3, since it has to be carried out afresh for each polyhedron type
and requires quite a few symbolic manipulations, algebraic and trigonometric.
.NH
The Iterative Solution.
.PP
We now describe the iterative solution of the fundamental system, based
on well-known Newton's method for solving nonlinear equations. The general
idea is to solve $2n$ of the unknown in terms of the $2n+1$'st, referred later
as the
.I independent
unknown, and to compute the latter by iterative
approximations. One of the problems in such an approach is the choice of the
independent unknown, and we will attend to it shortly.
.PP
First, we notice that the $alpha sub i$'s are readily available from (1):
.EQ (4)
alpha sub i = pi / n sub i
.EN
for $i=1, ... ,m$.
.PP
Furthermore, once one of the $gamma sub i$'s, say $gamma sub 1$,
is computed, all the rest are available from (3):
.EQ (5)
cos a = {cos alpha sub 1} / {sin gamma sub 1}
.EN
.EQ (6)
gamma sub i = arc sin ( {cos alpha sub i} / {cos a} )
.EN
for $i=2, ... ,m$.
.PP
Note that the inverse sine
function in (6) has seemingly two values in the range $(0, pi )$.
However, it may be easily observed that at most one of the $gamma sub i$'s may
be obtuse, and we may assume, without any loss of generality,
that $gamma sub i$, for $i=2, ... ,m$, are all acute.
.PP
Thus, (2) may be rewritten as
.EQ (7)
delta = pi - sum gamma sub i =0,
.EN
where $delta$ is a well defined function of $gamma sub 1$ only.
.PP
We recall Newton's method for solving the equation $f(x)=0$:
Choose an initial approximation to the root and then define
a sequence of closer approximations using the recursion
.EQ (8)
x hat =x- f(x) / {f prime (x)}
.EN
.PP
Assume initially that the fundamental triangles are approximately
planar. This motivates the initial approximation
.EQ
gamma sub i = pi#2 - alpha sub i.
.EN
for $i=1, ... ,m$.
.PP
This certainly satisfies (5) and (6) (with $cos a=1$), but as these
values for the $gamma sub i$'s are smaller than in reality (as the sum of the
angles in a spherical triangle exceeds $pi$),
$delta$ in (7) will not vanish, but rather be a positive number,
which motivates naming it the
.I "excess function" .
The iterative procedure
will converge if we are able to make the excess arbitrarily small.
It may be shown, at least empirically, that in order to guarantee convergence
it is sometimes necessary to choose $gamma sub 1$ as the biggest of
the initial values, i.e., choose $alpha sub 1$ to be the smallest of the
$alpha sub i$'s, or, in view of (4), choose $n sub 1$ to be the biggest of the
$n sub i$'s.
.PP
This choice is the obvious the case for those polyhedra for which
$gamma sub 1$ turn to be obtuse, in view of our observation about the
double-valuedness of the inverse sine function.
Also, it may be shown that in the general case, this choice also guarantees
a faster convergence than then any other choice. We'll see why it happens
once we developed the recursion formula.
.PP
To use (8), we have to differentiate the excess function;
we have from (7),
.EQ (9)
- {d delta} / {d gamma sub 1} = 1 + sum prime {d gamma sub i} / {d gamma sub 1}
.EN
(with the prime denoting summation over the range $2, ... ,m$).
However, in view of (5) and (6),
.EQ
sin gamma sub i = {sin gamma sub 1 cos alpha sub i} / {cos alpha sub 1}
.EN
which in turn implies, using logarithmic differentiation,
.EQ (10)
{d gamma sub i} / {d gamma sub 1} = {tan gamma sub i} / {tan gamma sub 1}.
.EN
Combining (7), (9) and (10) we get
.EQ
- delta / {delta prime} = delta {tan gamma sub 1} / {sum tan gamma sub i}
.EN
(with summation again over the full range $1, ... ,m$,
and $delta prime$ is the derivative in (9)).
.PP
Finally, we arrive at the required recursion for $gamma sub 1$:
.EQ
gamma hat sub 1 = gamma sub 1 + delta {tan gamma sub 1} / {sum tan gamma sub i}
.EN
.PP
In practice, we notice that the faces meeting at a vertex are not
necessarily different, thus we may group similar faces together, and adjust
the above formulas to reflect the fact that at each vertex the polyhedron
can have $m sub i$ faces each of which is a {$n sub i$},
with $sum m sub i = m$. Furthermore, we handle retrograde faces by
orienting the vertex figure so that the the first, thus biggest, face is
not retrograde. Thus, $n sub i$ is a positive rational,
and $m sub i$ is a positive integer. $d$, the vertex density, is a non-negative
integer.
.PP
To summarize, fundamental system
.EQ
n sub i alpha sub i = pi
.EN
.EQ
sum m sub i gamma sub i = pi d
.EN
.EQ
{cos alpha sub i} / {sin gamma sub i} = cos a
.EN
where $n sub 1 = max n sub i$,
has the following iterative solution algorithm:
.IP "Step 1."
Choose the initial approximation
$gamma sub i = pi#2 - alpha sub i$,
where $alpha sub i = pi / n sub i$.
.IP "Step 2."
Compute the excess $delta = pi d - sum m sub i gamma sub i$.
If it is numerically small enough, finish. Otherwise, continue to step 3.
.IP "Step 3."
Compute the next approximation to the independent unknown
$gamma sub 1$ using the recursion
.EQ
gamma hat sub 1 = gamma sub 1 +
delta {tan gamma sub 1} / {sum m sub i tan gamma sub i}
.EN
.IP "Step 4."
Compute $cos a$ and $gamma sub i$, $i = 2, ... ,m$, using
.EQ
cos a = {cos alpha sub 1} / {sin gamma sub 1}
.EN
.EQ
gamma sub i = arc sin ( {cos alpha sub i} / {cos a} )
.EN
.IP "Step 5."
Return to step 2.
.PP
We want to make an observation about the convergence of this algorithm.
The increment in $gamma sub 1$ in step 3 may be very small even without
the excess $delta$ being small. This happens if the denominator
$sum m sub i tan gamma sub i$ is large, unless the numerator
$tan gamma sub 1$ behaves similarly.
In such cases the algorithm converges slowly or even diverges,
and our choice for the independent unknown prevent them from occurring.
By the way, choosing $cos a$ as the independent unknown creates similar problems
and although it looks plausible and perhaps more elegant
(compare with the well known
.I "Lagrange multipliers"
), it should be avoided.
A mathematically rigorous proof of convergence is out of the scope of this
paper; We will have to be satisfied by empirical convergence for all the
finitely many uniform polyhedra (cf. [CLM], [S]).
.PP
Note that in few exceptional cases, the direct approach fails.
In these cases, it happens that the vertex density $d$ is zero,
and the faces incident at a vertex occur in several oppositely oriented pairs,
and thus even the initial approximation satisfies the fundamental system,
which is obviously impossible, since, as we already remarked,
$alpha sub i + gamma sub i > pi#2$ in a right-angled spherical triangle.
It is interesting to note that these polyhedra are exactly those which
cannot be constructed directly using the
.I Wythoff
construction, to be presented in the section 4.
In section 5 we present an adjustment to the construction,
which in turn leads to an adjustment to the fundamental system,
which makes it possible to handle these exceptions.
.NH
The Kaleidoscope.
.PP
We start by discussing the
.I "dihedral kaleidoscope" .
It consists of two hinged planar mirrors.
The reflections in these mirrors generate a group of
isometries, which is finite if the dihedral angle of the kaleidoscope is
a rational submultiple of $pi$, i.e., of the form
$pi / q$, where $q$ is a rational greater than one.
We now consider the meaning of these particular angles from additional
points of view.
.PP
Intersect the kaleidoscope by a perpendicular plane,
and choose a circle in this plane with center at the corner.
The kaleidoscope encloses a circular arc, and we may ask for
the cases in which repeated reflections of this arc in the mirrors produce
a finite covering of the circle.
It is easy to see that a $d$-fold covering obtained if $q = n / d$,
where $n$ and $d$ are relatively prime positive integers, with $n > d$.
In this case the the kaleidoscope generates $D sub n$, the dihedral group
of order $2n$, and the $pi / q = {pi d} / n$ arc
consists of $d$ copies of the fundamental domain of the group,
a $pi / n$ arc.
.PP
Now, put a point object in a general position on the enclosed arc.
Then, repeated reflections in the mirrors will yield $2n$ points.
which may naturally be viewed as the vertices of a $2n$-gon, where
adjacent vertices belong to arcs which share an endpoint.
Let the $2n$-gon be $C sub 1 C sub 2 ... C sub 2n$, where $C sub 1$
is the point object.
.PP
Note, that in two cases we get a smaller number of images:
The first case is when $C sub 1 = C sub 2$ or $C sub 1 = C sub 2n$, which means
that $C sub 1$ is a fixed point of one of the original reflections,
or, geometrically, that the point object is located on one of the mirrors.
Then, we get $n$ pairs of coincident adjacent vertices,
which means that $n$ of the edges of the polygon are degenerate,
and may be discarded. Thus, when the point object is located
on one of the mirrors,
we get regular $n$-gon, with density $d$, customarily denoted by
{$n / d$}, i. e., {$q$}.
Note, that if {$q$} and {$q prime$} satisfy $1 / q + 1 / {q prime} = 1$, they
are two oppositely oriented copies of the same polygon.
.PP
The other case is when $C sub n+1$ = $C sub 1$.
This is only possible if the $n+1$st arc coincides with the first, but
oppositely oriented. Thus, $C sub 1$ is located on the bisecting plane
of the kaleidoscope, and the reflection in this plane belongs to
to the dihedral group generated by the kaleidoscope.
In this case we have no degenerate edges, but rather a regular $n$-gon
which is transversed twice.  As the density of the compound is $d$,
$d$ has to be even and each polygon has density $d / 2$.
Thus, when the point object is located on the bisector,
we get a double {$n / (d/2)$}, i.e., a double {$2q$}.
It is easy to check that if the point object
is similarly located but the denominator $d$ is odd,
it traces a single regular $2n$-gon with density
$d$, i.e., a single {$2q$}.
.PP
In all the other cases the polygon is an irregular $2n$-gon, however
if we use only rotations (or any even number of reflections)
then the polygon $C sub 1 C sub 3 ... C sub 2n-1$ is still regular, a {$q$}.
.PP
We now add a third mirror, and get the
.I "trihedral kaleidoscope" ,
which consists of three concurrent planar mirrors.
The problem of finding conditions on the dihedral angles for the kaleidoscope
to generate a finite group of isometries was posed and solved by A. H. Schwarz
in 1873.
As we have already seen, it is necessary that these angles are
rational submultiples of $pi$, but however this is not sufficient.
Intersecting the kaleidoscope by a sphere centered in its corner,
Schwarz formulated the following problem:
Enumerate all convex spherical triangles $PQR$,
with angles $pi / p$, $pi / q$ and $pi / r$ ($p$,$q$,$r$
are all rational greater than one),
with the property that when reflected in
its sides any number of times, $PQR$ produces a finite covering of the sphere.
Such a triangle is called a
.I "Schwarz triangle"
and is denoted by the symbol $(p~q~r)$.
It may be shown that unless two of the angles are $pi#2$
(in which case the kaleidoscope generates the dihedral symmetry group),
$p$, $q$, and $r$ may have as numerators the numbers
$2$, $3$, $4$ or $5$, with the further stipulation that $4$ and $5$ cannot
occur together. The denominator has to be smaller than the numerator, and
this makes the number of nondihedral Schwarz triangles finite.
A complete list of Schwarz triangles may be found in [C], table III,
and in appendix I.
.PP
Putting a point object $C$ in the Schwarz triangle $PQR$,
it is now reflected repeatedly
to produce a polyhedron, whose vertices are the images of the point
object. As before, two vertices are considered adjacent if they belong
to triangles which share an edge, and several vertices are incident to the same
face if they belong to triangles which share a vertex.
Note that as in the previous discussion,
the polyhedron may be degenerate:
Two images may coincide without a similar coincidence of the Schwarz triangles.
This means that the polyhedron may be split into several, not necessarily
distinct, polyhedra.
This phenomenon is investigated in [CLM], and we will not discuss it here
any detail (but see however section 5).
.PP
The kaleidoscopic construction of polyhedra is named after Wythoff (1918)
who was the first to use it (in four dimensions, cf. [CLM], p. 406).
.PP
Assuming nondegeneracy, Wythoff construction is very useful in getting
the topological invariants of the traced polyhedra, that is, the covering
density $D$ and the Euler characteristic $chi$.
Both values can be easily computed
for the for the multiple tiling of the sphere by Schwarz triangle:
$D$ may be found from the area of $(p~q~r)$
and the order $g$ of the symmetry group generated by the reflection
in its sides:
.EQ
4 pi D = g ( pi / p + pi / q + pi / r - pi ),
.EN
or,
.EQ
D = g / 4 ( 1 / p + 1 / q + 1 / r - 1 ).
.EN
Note that the value of g is $4n$ , $24$, $48$ or $120$
if the group is $n$-fold dihedral, tetrahedral, octahedral or icosahedral,
respectively.
As pointed out in [CLM] (p. 412, 418, 425), this is also  the correct value
for the density of any polyhedron derivable from $(p~q~r)$, except for the cases
where the spherical polyhedron possesses faces which are
hemispherical or concave (i.e., bigger than a hemisphere).
In the former case, the planar faces are incident at the center,
and the density is not well-defined.  In the latter case, the spherical and
planar faces occur on two different sides of the center, and the density
of the planar polyhedron  may be computed by subtracting the density of the
spherical polyhedron above from the number of concave faces
(see the tables in appendix II; in our notation, a face is concave if $gamma$
is obtuse, see section 3).
.PP
The Euler characteristic relates $V$, the number of vertices,
$E$, the number of edges, and $F$, the number of faces of any map drawn
on a given closed surface by the famous Euler formula $V - E + F = chi$.
Here, we are considering a $D$-sheeted Riemann surface, which is triangulated
by the Schwarz triangles, so that $F = g$, $E= 3g / 2$, and $V = V sub p + V sub q + V sub r$, where $V sub q$ is the number of vertices with the angle
$ pi / q $, i.e., $V sub q = g / { 2 n sub q }$, where $n sub q$ is
the numerator of $q$. Thus, we get the formula
.EQ
chi = g / 2 ( 1 / n sub p + 1 / n sub q + 1 / n sub r  - 1 )
.EN
This value is also inherited by any non-degenerate polyhedron
derivable from $(p~q~r)$ (see the tables in appendix II; see section 5
for the degenerate cases). It is very interesting to note that $chi$ depends
upon the numerators only. This means, for instance,
that the convex Plato's icosahedron and
the star-cornered Poinsot's great icosahedron,
derivable from $(2~3~5)$ and $(2~3~5#2 )$, have both Euler characteristic 2,
and are thus homeomorphic as closed surfaces, although their densities
are much different (1 for the former, 7 for the latter).
.PP
It is clear, that wherever we put a point $C$ in the Schwarz triangle
$PQR$, the traced polyhedron will be isogonal, i. e., all its vertices will
be equivalent under the action of the isometry group generated by the three
reflections.
We will now discuss the positions of $C$ which guarantee that the
traced faces will be regular polygons, and study the corresponding spherical
tiling and the fundamental triangulation and its triangular prototiles
$A sub i B sub i C$.
As before, $A sub 1 A sub 2 ...$ will be the prototile of the dual tiling,
and $B sub 1 B sub 2 ...$ the vertex figure.
.PP
.NH 2
$C$ is at the vertex $P$ of $PQR$.
.PP
Let $A sub 1$ and $A sub 2$ be the vertices $Q$ and $R$ respectively,
and let $B sub 1$ be the foot of the perpendicular from $P$ on $QR$.
.PP
The resulting fundamental equations are, setting $p = n / d$:
.EQ
q alpha sub 1 = r alpha sub 2 = pi ,
.EN
.EQ
n gamma sub 1 + n gamma sub 2 = pi d .
.EN
By reflecting $PQR$ repeatedly in its sides,
we get the sequences of vertices
$A sub 1 A sub 2 A sub 3 ...$ and
$B sub 1 B sub 2 B sub 3 ...$,
which repeat themselves after $2n$ terms.
.PP
The resulting polyhedron is denoted by the Wythoff symbol $p|q~r$.
Its vertex configuration is $(q.r.q.r. ... .q.r)$ ($2n$ terms),
and its vertex density is $d$.
The vertex figure and the dual prototile are $2n$-gons.
.PP
.NH 2
$C$ is at the intersection of the side $PQ$ with bisector of the opposite
angle $R$.
.PP
Let $A sub 1$, $A sub 2$ and $A sub 3$ be the vertices $Q$, $R$ and $P$,
and let $B sub 1$ and $B sub 2$ be the feet of the perpendiculars from $C$ on
$QR$ and $RP$, respectively.
.PP
The resulting fundamental equations are:
.EQ
q alpha sub 1 = 2r alpha sub 2 =  p alpha sub 3 = pi ,
.EN
.EQ
gamma sub 1 +2 gamma sub 2 + gamma sub 3 = pi .
.EN
By reflecting $A sub 2$, $B sub 1$ and $B sub 2$ in $QR$, we get the images
$A sub 4$, $B sub 4$ and $B sub 3$, respectively.
.PP
The resulting polyhedron is denoted by the Wythoff symbol
$p~q|r$, and its vertex configuration is $(p.2r.q.2r)$.
The vertex figure and the dual prototile are quadrilaterals.
.PP
.NH 2
$C$ is at the incenter of $PQR$.
.PP
Let $A sub 1$, $A sub 2$  and $A sub 3$ be the vertices $P$, $Q$ and $R$,
and let $B sub 1$, $B sub 2$ and $B sub 3$ be the feet of the perpendiculars
from $C$ on $PQ$, $QR$ and $RP$, respectively.
.PP
The resulting fundamental equations are:
.EQ
2p alpha sub 1 = 2q alpha sub 2 = 2r alpha sub 3 = pi ,
.EN
.EQ
gamma sub 1 + gamma sub 2 + gamma sub 3 = pi .
.EN
.PP
The resulting polyhedron is denoted by the Wythoff symbol $p~q~r|$,
and its vertex configuration is $(2p.2q.2r)$.
The vertex figure and the dual prototile are triangles.
.PP
.NH 2
$C$ traces a snub polyhedron.
.PP
In the previous positions, the symmetry group of the polyhedron is generated
by reflections. In particular, the polyhedron is reflexible. We now discuss
a fourth position, which usually traces a chiral polyhedron, i.e.,
a polyhedron with a symmetry group which consists of rotations only\**.
.FS
However, $(5/2~3~3)$ and $(3/2~3/2~5/2)$ being isosceles, they yield
reflexible snub polyhedra.
.FE
This is done by considering
only images under an even number of reflections (as was done for the dihedral
kaleidoscope). In this case, it is easier to study the dual tiling directly,
and to infer the existence of $C$ without an actual construction.
.PP
Let $O$ be the
.I Fermat
point of the Schwarz triangle $PQR$, i.e, the point where the sides subtend
equal angles (assuming it exists\**).
.FS
The existence of $O$ is verified by a continuity argument,
at least for the case where all the angles of $PQR$ are smaller then $2 pi /3$
(this is not the case for $(3/2~3/2~5/2)$ and $(3/2~5/3~2)$).
.FE
Reflect $O$ in the sides and get an hexagon
$A sub 1 A sub 2 ... A sub 6$ with angles ${2 pi} / 3$,
${2 pi} / p$, ${2 pi} / 3$, ${2 pi} / q$, ${2 pi} / 3$ and
${2 pi} / r$ respectively,
where odd indices refer to the images of $O$, and even indices refer to the
vertices $P$, $Q$ and $R$.
Reflecting this hexagon any even number of times, we get an isohedral,
vertically regular tiling of the sphere, i.e., the dual of a uniform tiling.
The latter consists of a {$p$}, a {$q$} and a {$r$} with centers at $P$,
$Q$ and $R$, respectively, alternating with three, so-called
.I snub ,
{$3$}'s. Let $C$ be the common vertex of these six polygons
(since the snub {$3$}'s are congruent, it is located at the circumcenter of
$A sub 1 A sub 3 A sub 5$),
and let $B sub i$, for $i=1,2, ... ,6$, be the foot of the perpendicular
from $C$ to $A sub i A sub i+1$.
.PP
The resulting fundamental equations are:
.EQ
3 alpha sub 1 = p alpha sub 2 = q alpha sub 4 = r alpha sub 6 = pi ,
.EN
.EQ
3 gamma sub 1 + gamma sub 2 + gamma sub 4 + gamma sub 6 = pi .
.EN
Here, we counted one snub {$3$} thrice, because the snub {$3$}s
are all congruent.
The resulting
.I snub
polyhedron is denoted by the Wythoff symbol $|p~q~r$,
and its vertex configuration is $(3.p.3.q.3.r)$.
The vertex figure and the dual prototile are hexagons.
.PP
Note that in all the cases, the occurrence of $alpha = pi#2$ implies
that the corresponding tile is a {$2$}, i.e., a digon, and may be discarded.
.PP
.NH
Exceptional Polyhedra.
.PP
An polyhedron is
.I orientable
if its faces may be coherently oriented, that is, assigned orientations
in such a way that the orientations induced on an edge common to two
faces are opposite.
It is easy to verify, that the Wythoff construction always yields
orientable polyhedra, assuming that vertices which belong to nonadjacent
Schwarz triangles are considered distinct, even if they coincide.
The number of the polyhedron vertices may be readily found by dividing
the order of the kaleidoscope symmetry group by the number of copies of
adjacent Schwarz triangles which share a vertex, i. e.,
by two for $p~q|r$ or $|p~q~r$,
and by $n$ for $n / d |q~r$.
.PP
We will now discuss two particular cases where the Wythoff construction
yields only pairs of coinciding vertices, that, when identified,
are the vertices of a nonorientable, or
.I one-sided ,
polyhedron.
In these cases, the number of real vertices will be of course only
a half of the expected number.
The discussion is based on the phenomenon, described in section 4,
that a point object on the bisector of a dihedral kaleidoscope
with angle $pi / q$, $q$ rational with an even denominator, yields
a double {$2q$}.
.PP
For conclusion, we shall have a brief, independent discussion about
the solution for the only non-Wythoffian polyhedron in existence.
.NH 2
Polyhedra $p~q~r|$ with an even denominator.
.PP
Consider a Schwarz triangle $PQR$, with an angle $pi / r$ at $R$,
$r$ rational with an even denominator.
Suppose the point object $C$ is located in the incenter of $PQR$.
In particular, it lies on the bisector at$R$. As we have seen,
the images of $C$ trace a {$2p$}, a {$2q$} and a {$2r$},
with centers at $P$, $Q$ and $R$,
respectively. However, since $r$ has an even denominator,
we find that the face with center at $R$, which is traced
by reflections at $RP$ and $RQ$ only, is a double {$2r$}.
When transversing it once, $PQR$ is reflected in the bisector at $R$, and the
faces with centers at $P$ and $Q$ are reflected into two similar
faces with centers at the images of $P$ and $Q$. Thus, in addition to the
double {$2r$}, we have at $C$ two {$p$}'s and two {$q$}'s, arranged in the
cyclic order $(2r.p.q.2r.q.p)$.
By discarding the double {$2r$}'s, we get a single, one-sided polyhedron.
The nonorientability is due to orientation reversal: Trying to find
a coherent orientation on the faces and considering the four faces incident
at a vertex, we notice that two of them has to be retrograde, i.e.,
the vertex configuration is $(p.q.p prime .q prime )$.
However, when considering the
faces adjacent to a discarded double {$2r$},
none of the four faces incident at a vertex may be retrograde.
.PP
It is interesting to note, that the enumeration of the faces at $C$ does not
define the polyhedron well, and the direct algorithmic approach in section 3
fails. However, by taking the {$2r$}'s into account,
and solving the equations set in section 4.3,
the metrical properties of these exceptional polyhedra
may be still computed.
.PP
The Euler characteristic can be obtained from the basic value discussed
in section 4: By considering the fundamental triangulation and removing
the double {$2r$}'s, the balance of edges and faces doesn't change, and
the number of vertices is reduced by $V sub r$ (see section 4).
Thus, we get for this case
.EQ
chi = g / 2 ( 1 / n sub p + 1 / n sub q - 1).
.EN
The density is not-well define, as these polyhedra do not produce an even
covering of the sphere.
.PP
.NH 2
Hemi polyhedra $p~p prime | r$.
.PP
Consider a Schwarz triangle $PQR$, where the angles $pi / p$
and $pi / q$ are complementary, and assume that $q = p prime < 2 < p$.
Reflecting the side $PR$ in $PQ$, we get an arc which meets the extension
of $RQ$ beyond $Q$ at a point $S$.
It is clear that the sides of the spherical triangle $PSR$ are all
arcs of symmetry of the group generated by $PQR$,
and thus it is itself a Schwarz triangle, say $( p / 2~s~r)$,
where $s$ is a rational greater than one.
It follows that the incenter $C$ of $PSR$ is also the point where
the side $PQ$ of $PQR$ meets the bisector of the opposite angle.
Thus, considering the polyhedra traced by the images of $C$,
we find that the polyhedra $p~p prime |r$ and $p / 2~s~r|$
have the same vertices.
Of course, the vertex configurations are different: $(p.2r.p prime .2r)$
for the former, $(p.2s.2r)$ for the latter.
However, if $s$ has an even denominator, the double {$2s$}'s in $p / 2~s~r|$
may discarded as above, and we are left with the vertex configuration
$(p.2r.p prime .2r)$, that is $p~p prime |r$.
The last term of the vertex configuration may be written as $2r$
rather than $(2r) prime$, because the {2r}'s are great circles, and thus
the same orientation can be designated either retrograde or not.
This property of the {$2r$}'s follows from the observation that
$C$ is the incenter of the lune obtained by extending
$RP$ and $RQ$ beyond $P$ and $Q$.
The property that such polyhedra possess equatorial faces which separate them
in half justifies labeling them
.I hemi .
.PP
It is interesting to note, that if $s$ has an even denominator,
than $CPS$ is the Schwarz triangle $(2~p~2s)$ (or, the hemi polyhedron
share the vertices with $2|p~2s$), where $2s$ has an odd numerator.
However, it may be shown that the only Schwarz triangle $(2~p~q)$
with $q$ rational, greater than two, and with an even numerator
is $(2~3~4)$. Thus, it follows that the only hemi polyhedron which is
orientable is $3~3#2 |3$ (cf. [CLM], p. 417).
.PP
In contrast to the previous case, it is easy to check that
the metrical properties of the polyhedron $p~p prime |r$
are computable from its vertex configuration, once we write it
$(p.2r.p prime .2r)$ rather than $(p.2r.p prime .(2r) prime )$.
In fact, just one step of the algorithm yields the exact result.
The geometric reason behind this contrast is related to the vertex
figure of the two types of nonorientable polyhedra (cf. [CLM],
p. 417 and 419): The vertex figure of a general $p q r|$ is a crossed
parallelogram, which is not determined given its sides and its
inscribability in a circle. However, the vertex figure of
$p~p prime |r$ is a crossed rectangle, and the extra information that
the crossed sides pass through the center of the circle does determine
the vertex figure.
.PP
As the Wythoff construction generates an orientable two sided covering
of $p~p prime | r$, its Euler characteristic is half of the basic
one, that is
.EQ
chi = g / 4 ( 2 / n sub p + 1 / n sub r - 1).
.EN
.PP
.NH 2
The last polyhedron $|3~5#2~3#2~5#3$.
.PP
The only uniform polyhedron which has more than six faces at a vertex,
and the only one which cannot be constructed by the Wythoff construction
(or a minute modification of it),
has the vertex configuration $(4. 5#2 .4.3.4. 5#3 .4. 3#2 )$.
Again, the enumeration of faces incident at a vertex does not determine
the polyhedron, and therefore a direct use of the uniform solution fails.
However, by considering the Schwarz triangle $( 3~5#2~5#3 )$
and its reflection in the perpendicular bisector of its shortest side
(which is an arc of symmetry of the generated group),
it may be shown (cf. [CLM], section 11), that the oppositely oriented
pairs of triangles and pentagrams of $|3~5#2~3#2~5#3$
also belong to an enantiomorphous and vertex sharing pair of $|3~5#2~5#3$'s.
Actually, both pentagrams belong to both snub polyhedra, with roles
interchanged, and each triangle is a non-snub triangle of one of
the pair. We can conclude easily that the last uniform polyhedron is
a second instance of an orientable hemi polyhedron.
Furthermore, solving the snub polyhedra as in section 4.4, we can complete the
solution by computing the triangulation of
the extra squares using the fundamental equation (3), section 2.
The Euler characteristic has the bizarre value of $chi = -56$, computable
from the actual counts of vertices, edges and faces.
.NH
References.
.IP [BC]
Ball, W. W. R & Coxeter, H. S. M.,
.I "Mathematical Recreations and Essays" ,
Thirteenth Edition, Dover, New York, 1987.
.IP [C]
Coxeter, H. S. M.,
.I "Regular Polytopes" ,
Third Edition, Dover, New York, 1973.
.IP [CLM]
Coxeter, H. S. M., Longuet-Higgins, M. S. & Miller, J. C. P.,
.I "Uniform Polyhedra" ,
Phil. Trans. Royal Soc. London, Ser. A, 246 (1953), 401-409.
.IP [CR]
Cundy, H. M. & Rollett, A. P.,
.I "Mathematical Models" ,
Third Edition, Tarquin, Stradbroke, 1981.
.IP [GMS]
Gru\*:nbaum, B., Miller, J. C. P. & Shephard, G. C.,
.I "Uniform Tilings with Hollow Tiles" ,
in
.I "The Geometric Vein - The Coxeter Festschrift" ,
C. Davis et al., eds.,
Springer-Verlag, New York, 1982, 17-64.
.IP [GS]
Gru\*:nbaum, B. & Shephard, G. C.,
.I "Tilings and Patterns" ,
Freeman, New York, 1987.
.IP [Ha]
Har'El, Z.,
.I "Kaleido - Kaleidoscopic Construction of Uniform Polyhedra" ,
Department of Mathematics, Technion, Haifa, 1992.
.IP [Hm]
Hume, A.,
.I "Exact Descriptions of Regular and Semi-regular Polyhedra and Their Duals" ,
Computing Science Technical Report No. 130, AT&T Bell Laboratories,
Murray Hill, 1986.
.IP [Hy]
Huybers, P.,
.I "Uniform Polyhedra for Building Structures" ,
Bull. Inter. Assos. Shells and Spatial Structures, 21 (1980), 27-38.
.IP [J]
Johnson, N. W.,
.I "Convex Polyhedra with Regular Faces" ,
Canad. J. Math., 18 (1966), 169-200.
.IP [L]
Lines, L.,
.I "Solid Geometry" ,
Dover, New York, 1961.
.IP [M]
Moritz, R.,
.I "On Napier's Fundamental Theorem Relating to Right Spherical Triangles" ,
Amer. Math. Monthly, 22 (1915), 220-222.
.IP [S]
Skilling, J.,
.I "The Complete Set of Uniform Polyhedra" ,
Phil. Trans. Royal Soc. London, Ser. A, 278 (1975), 111-135.
.IP [W1]
Wenninger, M. J.,
.I "Polyhedron Models" ,
Cambridge University Press, Cambridge, 1971.
.IP [W2]
Wenninger, M. J.,
.I "Dual Models" ,
Cambridge University Press, Cambridge, 1984.
.bp
.SH
Appendix I: Schwarz Triangles.
.PP
To facilitate the enumeration of Schwarz triangles,
one notices that for the covering to be simple, $(p~q~r)$ must be a
.I "Mo\*:bius triangle" ,
that is, one of the triangles $D sub 1/n = (2~2~n)$
(with $n=2,3, ...$),
$T sub 1 =(2~3~3)$, $O sub 1 =(2~3~4)$ and $I sub 1 =(2~3~5)$,
which are the fundamental domains of the full dihedral, tetrahedral,
octahedral and icosahedral symmetry groups, respectively.
A Schwarz triangle which produces a $d$-fold covering of the sphere can be
decomposed to $d$ copies of one of the Mo\*:bius triangles.
These properties may be used to synthesize Schwarz triangles, as we now explain.
.PP
Let
.EQ
S sub 1 = (p~x~r sub 1 ~;~y~v~w sub 1 )
.EN
and
.EQ
S sub 2 = (x prime ~q~r sub 2 ~;~u~y~w sub 2 )
.EN
be two Schwarz triangles (where we included in the symbol also the sides
opposite the respective angles),
which have a common edge $y$ and complementary angles
$pi / x$ and $pi / {x prime}$.
Then, $S sub 1$ and $S sub 2$ can be pasted along the common edge, and produce
a new triangle
.EQ
S sub 1 +S sub 2 = (p~q~r~;~u~v~w) ,
.EN
where we have set
.EQ
1 / r = 1 / r sub 1 + 1 / r sub 2 ,
.EN
.EQ
w=w sub 1 +w sub 2 .
.EN
This is a Schwarz triangle if $r > 1$.
As usual, $2 S$ is a shorthand for $S + S$.
.PP
In few cases, $S sub 1$ and $S sub 2$ can be pasted together in more then one
way, to produce several different Schwarz triangles.
In particular,
if $S sub 1$ and $S sub 2$ are two copies of the same
right-angled triangle $(p~q~2~;~u~v~w)$, with $p,q>2$ and $p != q$,
they can be pasted along each of the legs,
to produce two
isosceles triangles, with the same area but different perimeter, namely
$(q~q~p / 2~;~w~w~2u)$ and $(p~p~q / 2~;~w~w~2v)$.
.PP
Starting from the Mo\*:bius triangles
we get the denumerable family of dihedral Schwarz triangles
$D sub d/n =(2 ~ 2 ~ n / d )$ (with $d=1, ... ,n-1$),
and the tetrahedral, octahedral and
icosahedral triangles listed in tables 1 through 3.
The triangles are arranged by increasing area: The area of
$I sub d$, for instance, is $d$ times the area of $I sub 1$.
In the cases where there are several triangles with the same area, they are ordered
by increasing perimeter and distinguished from one another by a letter,
e.g., $I sub 2a$ and $I sub 2b$.
The sides are given in terms of the legs $s$, $u$ and $v$ of $T sub 1$ and $I sub 1$\**.
.FS
It may be shown that $cos 2s = -  1 / 3$, $cos 2u = sqrt 5 / 3$ and
$cos 2v = sqrt 5 / 5$.
.FE
Because of space considerations,
we list just one of the several ways to split each Schwarz
triangle into smaller ones. It is interesting that every triangle (except
the smallest) can always be split into two triangular pieces,
with only one exception:
The the trirectangular triangle $D sub 1/2$, if considered as an icosaheral
Schwarz triangle, can only be split into four pieces or more.
The listed splitting is the symmetric one: An equilateral triangle,
$( 5#2~5#2~5#2 )$, surrounded by three copies of its half, the right-angled
triangle $(5~5#2~2)$.
Triangles which belong to a proper symmetry subgroup are flagged.
.sp 5
.TS
center box ;
cb s s s s s
c|c|c s s|c
l|l|l l l|l .
Table 1: Tetrahedral Schwarz Triangles
_
	symbol	sides	splitting
_
$T sub 1$	$(3~3~2)$	$s$	$s$	$pi -2s$
$T sub 2$	$(3~3~3#2 )$	$pi -2s$	$pi -2s$	$2s$	$2T sub 1$
$T sub 3$	$(3~2~3#2 )$	$s$	$2s$	$pi -s$	$T sub 1 +T sub 2$
$T sub 5$	$(2~3#2~3#2 )$	$pi -2s$	$pi -s$	$pi -s$	$T sub 2 +T sub 3$
$T sub 6$	$( 3#2~3#2~3#2 )$	$2s$	$2s$	$2s$	$2 T sub 3$
.TE
.sp 5
.TS
center box ;
cb s s s s s s
c|c|c s s|c|c
l|l|l l l|l|l .
Table 2: Octahedral Schwarz Triangles
_
	symbol	sides	splitting	
_
$O sub 1$	$(4~3~2)$	$pi#2 -s$	$pi#4$	$s$
$O sub 2a$	$(3~3~2)$	$s$	$s$	$pi -2s$	$2 O sub 1$	$T sub 1$
$O sub 2b$	$(4~4~3#2 )$	$s$	$s$	$pi#2$	$2 O sub 1$
$O sub 3$	$(4~2~2)$	$pi#4$	$pi#2$	$pi#2$	$O sub 1 +O sub 2a$	$D sub 1/4$
$O sub 4a$	$(3~3~3#2 )$	$pi -2s$	$pi -2s$	$2s$	$2O sub 2a$	$T sub 2$
$O sub 4b$	$(4~3~4#3 )$	$s$	$pi#2$	$pi -s$	$O sub 2a +O sub 2b$
$O sub 5$	$(4~2~3#2 )$	$pi#2 -s$	$pi -s$	$3pi#4$	$O sub 1 +O sub 4b$
$O sub 6a$	$(2~2~2)$	$pi#2$	$pi#2$	$pi#2$	$2 O sub 3$	$D sub 1/2$
$O sub 6b$	$(3~2~3#2 )$	$s$	$2s$	$pi -s$	$O sub 2a + O sub 4a$	$T sub 3$
$O sub 7$	$(3~2~4#3 )$	$pi#4$	$pi -s$	$pi#2 +s$ 	$O sub 3 +O sub 4b$
$O sub 9$	$(2~2~4#3 )$	$pi#2$	$pi#2$	$3pi#4$	$O sub 4b +O sub 5$	$D sub 3/4$
$O sub 10$	$(2~3#2~3#2 )$	$pi - 2s$	$pi -s$	$pi -s$	$2 O sub 5$	$T sub 5$
$O sub 11$	$(2~3#2~4#3 )$	$s$	$3pi#4$	$pi#2 +s$	$O sub 6b +O sub 5$
$O sub 12$	$( 3#2~3#2~3#2 )$	$2s$	$2s$	$2s$	$2 O sub 6b$	$T sub 6$
$O sub 14$	$( 3#2~4#3~4#3 )$	$pi#2$	$pi -s$	$pi -s$	$2 O sub 7$
.TE
.bp
.TS H
center box ;
cb s s s s s s
c|c|c s s|c|c
l|l|l l l|l|l .
Table 3: Icosahedral Schwarz Triangles
_
	symbol	sides	splitting	
_
.TH
$I sub 1$	$(5~3~2)$	$u$	$v$	$pi#2 -u-v$
$I sub 2a$	$(3~3~5#2 )$	$pi#2 -u-v$	$pi#2 -u-v$	$2u$	$2 I sub 1$
$I sub 2b$	$(5~5~3#2 )$	$pi#2 -u-v$	$pi#2 -u-v$	$2v$	$2 I sub 1$
$I sub 3$	$(5~5#2~2)$	$v$	$pi#2 -v$	$2v$	$I sub 1 +I sub 2b$
$I sub 4$	$(5~3~5#3 )$	$pi#2 -u-v$	$2v$	$pi#2 +u-v$	$I sub 2a +I sub 2b$
$I sub 6a$	$( 5#2~5#2~5#2 )$	$2v$	$2v$	$2v$	$2 I sub 3$
$I sub 6b$	$(5~3~3#2 )$	$2u$	$pi#2 +u-v$	$pi#2 -u+v$	$I sub 2a +I sub 4$
$I sub 6c$	$(5~5~5#4 )$	$2v$	$2v$	$pi -2v$	$2 I sub 3$
$I sub 7$	$(3~5#2~2)$	$pi#2 -v$	$pi#2 -u$	$pi#2 +u-v$	$I sub 3 +I sub 4$
$I sub 8$	$(5~5#2~3#2 )$	$pi#2 -u-v$	$pi#2 -u+v$	$pi -2v$	$I sub 2a +I sub 6b$
$I sub 9$	$(5~2~5#3 )$	$v$	$pi -2v$	$pi#2 +v$	$I sub 3 +I sub 6c$
$I sub 10a$	$(3~5#2~5#3 )$	$2v$	$pi#2 +u-v$	$pi#2 -u+v$ 	$I sub 4 +I sub 6a$
$I sub 10b$	$(5~3~5#4 )$	$pi#2 -u-v$	$pi -2v$	$pi#2 +u+v$	$I sub 4 +I sub 6c$
$I sub 11$	$(5~2~3#2 )$	$u$	$pi#2 +u+v$	$pi -v$	$I sub 1 +I sub 10b$
$I sub 13$	$(3~2~5#3 )$	$pi#2 -v$	$pi#2 -u+v$	$pi#2 +u$	$I sub 6b +I sub 7$
$I sub 14a$	$( 5#2~5#2~3#2 )$	$pi#2 +u-v$	$pi#2 +u-v$	$pi -2v$	$2 I sub 7$
$I sub 14b$	$(3~3~5#4 )$	$pi#2 +u-v$	$pi#2 +u-v$	$pi -2u$	$2 I sub 7$
$I sub 15$	$(2~2~2)$	$pi#2$	$pi#2$	$pi#2$	$I sub 6a +3I sub 3$	$D sub 1/2$
$I sub 16$	$(3~5#2~5#4 )$	$2v$	$pi#2 -u+v$	$pi#2 +u+v$	$I sub 6a +I sub 10a$
$I sub 17$	$( 5#2~2~3#2 )$	$pi#2 -u$	$pi#2 -u+v$	$pi#2 +v$	$I sub 8 +I sub 9$
$I sub 18a$	$( 5#2~5#3~5#3 )$	$2v$	$pi -2v$	$pi -2v$	$2 I sub 9$
$I sub 18b$	$(3~5#3~3#2 )$	$pi#2 -u-v$	$pi -2u$	$pi#2 +u+v$	$I sub 8 + I sub 10b$
$I sub 19$	$(3~2~5#4 )$	$v$	$pi#2 +u+v$	$pi -u$	$I sub 9 +I sub 10b$
$I sub 21$	$( 5#2~2~5#4 )$	$pi#2 -v$	$pi -2v$	$pi -v$	$I sub 10b +I sub 11$
$I sub 22$	$( 5#2~3#2~3#2 )$	$2u$	$pi#2 +u+v$	$pi#2 +u+v$	$2 I sub 11$
$I sub 23$	$(2~5#3~3#2 )$	$pi#2 +u-v$	$pi#2 +u$	$pi#2 +v$	$I sub 10a +I sub 13$
$I sub 26$	$( 5#3~5#3~3#2 )$	$pi#2 -u+v$	$pi#2 -u+v$	$pi -2v$	$2 I sub 13$
$I sub 27$	$(2~5#3~5#4 )$	$2v$	$pi#2 +v$	$pi -v$	$I sub 11 +I sub 16$
$I sub 29$	$(2~5#2~5#4 )$	$pi#2 -u-v$	$pi -v$	$pi -u$	$I sub 11 +I sub 18b$
$I sub 32$	$( 5#3~3#2~5#4 )$	$pi#2 +u-v$	$pi -2v$	$pi#2 +u+v$	$I sub 14a +I sub 18a$
$I sub 34$	$( 3#2~3#2~5#4 )$	$pi#2 -u+v$	$pi#2 -u+v$	$pi -2u$	$2 I sub 17$
$I sub 38$	$( 3#2~5#4~5#4 )$	$2v$	$pi#2 +u+v$	$pi#2 +u+v$	$2 I sub 19$
$I sub 42$	$( 5#4~5#4~5#4 )$	$pi -2v$	$pi -2v$	$pi -2v$	$2 I sub 21$
.TE
.bp
.SH
Appendix II: Uniform Polyhedra
.PP
In tables 4 to 8, we list the seventy-five nondihedral uniform polyhedra,
as well as the five pentagonal prisms and antiprisms, grouped by
generating Schwarz triangles. For each polyhedron we indicate a figure
number in this appendix, its Wythoff and vertex configuration symbols,
and the values of its Euler characteristic $chi$ and density $D$
(if well-defined).
Nonorientable polyhedra are marked by starring their characteristic.
For reference,  we indicate for each polyhedron a figure number in [CLM],
pp. 439-448, and a model number in [W1].
The polyhedron names listed in tables 5 to 8 are taken from [W2],
where they are attributed to Norman W. Johnson,
but note they sometimes vary among authors.
Our figures represent wire-frame images of the
listed uniform polyhedra and their duals
(the latter are indicated by a starred figure number\**).
.FS 
The ten unbounded polyhedra in figures
8*,9*,20*,54*,56*,66*,68*,75*,76*,80*
are different from their [W2] counterparts.
They use the
.I "more correctly shown"
faces of [W2], p. 103.
.FE
Although the figures are two dimensional, depth is faithfully
represented by the variable thickness of the wires.
The drawings were made using the UNIX\**
.FS
UNIX is a trademark of AT&T Bell Laboratories.
.FE
utility
.I pic ,
from directives generated by
.I kaleido
(cf. [Ha]).
.PP
.sp 4
.TS
center box ;
cb s s s s s s
c|c|c s|cp-2|c|c
c|c|c s|cp-2|c|c
c|c|c|c|lp-2|c|c .
Table 4: Dihedral Uniform Polyhedra
_
	fig	symbol	name	$chi$	$D$
	\^	\^	\fIdual\fR	\^	\^
_
$D sub 1/5$	1	$2~5|2$	$(4.4.5)$	pentagonal prism	2	1
\^	\^	\^	\^	\fIpentagonal dipyramid\fR	\^	\^
\^	2	$|2~2~5$	$(3.3.3.5)$	pentagonal antiprism	2	1
\^	\^	\^	\^	\fIpentagonal deltohedron\fR	\^	\^
_
$D sub 2/5$	3	$2~5#2 |2$	$(4.4. 5#2 )$	pentagrammic prism	2	2
\^	\^	\^	\^	\fIpentagrammic dipyramid\fR	\^	\^
\^	4	$|2~2~5#2$	$(3.3.3. 5#2 )$	pentagrammic antiprism	2	2
\^	\^	\^	\^	\fIpentagrammic deltohedron\fR	\^	\^
_
$D sub 3/5$	5	$|2~2~5#3$	$(3.3.3. 5#3 )$	pentagrammic crossed antiprism	2	3
\^	\^	\^	\^	\fIpentagrammic concave deltohedron\fR	\^	\^
.TE
.sp 4
.TS
center box ;
cb s s s s s s
c|c|c s|cp-2|c|c|c
c|c|c s|cp-2|c|c|c
c|c|c|c|lp-2|c|c|c .
Table 5: Tetrahedral Uniform Polyhedra
_
	fig	symbol	name	$chi$	$D$	ref
	\^	\^	\fIdual\fR	\^	\^	\^
_
$T sub 1$	6	$3|2~3$	$(3.3.3)$	tetrahedron	2	1	15,1
\^	\^	\^	\^	\fItetrahedron\fR	\^	\^	\^
\^	7	$2~3|3$	$(6.6.3)$	truncated tetrahedron	2	1	16,6
\^	\^	\^	\^	\fItriakistetrahedron\fR	\^	\^	\^
_
$T sub 2$	8	$3#2~3|3$	$(6. 3#2 .6.3)$	octahemioctahedron	0		37,68
\^	\^	\^	\^	\fIoctahemioctacron\fR	\^	\^	\^
_
$T sub 3$	9	$3#2~3|2$	$(4. 3#2 .4.3)$	tetrahemihexahedron	1*		36,67
\^	\^	\^	\^	\fItetrahemihexacron\fR	\^	\^	\^
.TE
.TS
center box ;
cb s s s s s s
c|c|c s|cp-2|c|c|c
c|c|c s|cp-2|c|c|c
c|c|c|c|lp-2|c|c|c .
Table 6: Octahedral Uniform Polyhedra
_
	fig	symbol	name	$chi$	$D$	ref
	\^	\^	\fIdual\fR	\^	\^	\^
_
$O sub 1$	10	$4|2~3$	$(3.3.3.3)$	octahedron	2	1	17,2
\^	\^	\^	\^	\fIcube\fR	\^	\^	\^
\^	11	$3|2~4$	$(4.4.4)$	cube	2	1	18,3
\^	\^	\^	\^	\fIoctahedron\fR	\^	\^	\^
\^	12	$2|3~4$	$(3.4.3.4)$	cuboctahedron	2	1	19,11
\^	\^	\^	\^	\fIrhombic dodecahedron\fR	\^	\^	\^
\^	13	$2~4|3$	$(6.6.4)$	truncated octahedron	2	1	20,7
\^	\^	\^	\^	\fItetrakishexahedron\fR	\^	\^	\^
\^	14	$2~3|4$	$(8.8.3)$	truncated cube	2	1	21,8
\^	\^	\^	\^	\fItriakisoctahedron\fR	\^	\^	\^
\^	15	$3~4|2$	$(4.3.4.4)$	rhombicuboctahedron	2	1	22,13
\^	\^	\^	\^	\fIdeltoidal icositetrahedron\fR	\^	\^	\^
\^	16	$2~3~4|$	$(4.6.8)$	truncated cuboctahedron	2	1	23,15
\^	\^	\^	\^	\fIdisdyakisdodecahedron\fR	\^	\^	\^
\^	17	$|2~3~4$	$(3.3.3.3.4)$	snub cube	2	1	24,17
\^	\^	\^	\^	\fIpentagonal icositetrahedron\fR	\^	\^	\^
_
$O sub 2b$	18	$3#2~4|4$	$(8. 3#2 .8.4)$	small cubicuboctahedron	\-4	2	38,69
\^	\^	\^	\^	\fIsmall hexacronic icositetrahedron\fR	\^	\^	\^
_
$O sub 4$	19	$3~4| 4#3$	$( 8#3 .3. 8#3 .4)$	great cubicuboctahedron	\-4	4	50,77
\^	\^	\^	\^	\fIgreat hexacronic icositetrahedron\fR	\^	\^	\^
\^	20	$4#3~4|3$	$(6. 4#3 .6.4)$	cubohemioctahedron	\-2*		51,78
\^	\^	\^	\^	\fIhexahemioctacron\fR	\^	\^	\^
\^	21	$4#3~3~4|$	$( 8#3 .6.8)$	cubitruncated cuboctahedron	\-4	4	52,79
\^	\^	\^	\^	\fItetradyakishexahedron\fR	\^	\^	\^
_
$O sub 5$	22	$3#2~4|2$	$(4. 3#2 .4.4)$	great rhombicuboctahedron	2	5	59,85
\^	\^	\^	\^	\fIgreat deltoidal icositetrahedron\fR	\^	\^	\^
\^	23	$3#2~2~4|$	$(8.4. 8#7 . 4#3 )$	small rhombihexahedron	\-6*		60,86
\^	\^	\^	\^	\fIsmall rhombihexacron\fR	\^	\^	\^
_
$O sub 7$	24	$2~3| 4#3$	$( 8#3 . 8#3 . 3 )$	stellated truncated hexahedron	2	7	66,92
\^	\^	\^	\^	\fIgreat triakisoctahedron\fR	\^	\^	\^
\^	25	$4#3~2~3|$	$( 8#3 .4.6)$	great truncated cuboctahedron	2	1	67,93
\^	\^	\^	\^	\fIgreat disdyakisdodecahedron\fR	\^	\^	\^
_
$O sub 11$	26	$4#3~3#2~2|$	$(4. 8#3 . 4#3 . 8#5 )$	great rhombihexahedron	\-6*		82,103
\^	\^	\^	\^	\fIgreat rhombihexacron\fR	\^	\^	\^
.TE
.bp
.TS H
center box ;
cb s s s s s s
c|c|c s|cp-2|c|c|c
c|c|c s|cp-2|c|c|c
c|c|c|c|lp-2|c|c|c .
Table 7: Icosahedral Uniform Polyhedra
_
	fig	symbol	name	$chi$	$D$	ref
	\^	\^	\fIdual\fR	\^	\^	\^
_
.TH
$I sub 1$	27	$5|2~3$	$(3.3.3.3.3)$	icosahedron	2	1	25,4
\^	\^	\^	\^	\fIdodecahedron\fR	\^	\^	\^
\^	28	$3|2~5$	$(5.5.5)$	dodecahedron	2	1	26,5
\^	\^	\^	\^	\fIicosahedron\fR	\^	\^	\^
\^	29	$2|3~5$	$(3.5.3.5)$	icosidodecahedron	2	1	28,12
\^	\^	\^	\^	\fIrhombic triacontahedron\fR	\^	\^	\^
\^	30	$2~5|3$	$(6.6.5)$	truncated icosahedron	2	1	27,9
\^	\^	\^	\^	\fIpentakisdodecahedron\fR	\^	\^	\^
\^	31	$2~3|5$	$(10.10.3)$	truncated dodecahedron	2	1	29,10
\^	\^	\^	\^	\fItriakisicosahedron\fR	\^	\^	\^
\^	32	$3~5|2$	$(4.3.4.5)$	rhombicosidodecahedron	2	1	30,14
\^	\^	\^	\^	\fIdeltoidal hexecontahedron\fR	\^	\^	\^
\^	33	$2~3~5|$	$(4.6.10)$	truncated icosidodechedon	2	1	31,16
\^	\^	\^	\^	\fIdisdyakistriacontahedron\fR	\^	\^	\^
\^	34	$|2~3~5$	$(3.3.3.3.5)$	snub dodecahedron	2	1	32,18
\^	\^	\^	\^	\fIpentagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 2a$	35	$3| 5#2~3$	$( 5#2 .3. 5#2 .3.  5#2 .3)$	small ditrigonal icosidodecahedron	\-8	2	39,70
\^	\^	\^	\^	\fIsmall triambic icosahedron\fR	\^	\^	\^
\^	36	$5#2~3|3$	$(6. 5#2 .6.3)$	small icosicosidodecahedron	\-8	2	40,71
\^	\^	\^	\^	\fIsmall icosacronic hexecontahedron\fR	\^	\^	\^
\^	37	$| 5#2 ~3~3$	$(3. 5#2 .3.3.3.3)$	small snub icosicosidodecahedron	\-8	2	41,110
\^	\^	\^	\^	\fIsmall hexagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 2b$	38	$3#2~5|5$	$(10. 3#2 .10.5)$	small dodecicosidodecahedron	\-16	2	42,72
\^	\^	\^	\^	\fIsmall dodecacronic hexecontahedron\fR	\^	\^	\^
_
$I sub 3$	39	$5|2~5#2$	$( 5#2 . 5#2 . 5#2 . 5#2 . 5#2 )$	small stellated dodecahedron	\-6	3	43,20
\^	\^	\^	\^	\fIgreat dodecahedron\fR	\^	\^	\^
\^	40	$5#2 |2~5$	$(5.5.5.5.5)/2$	 great dodecahedron	\-6	3	44,21
\^	\^	\^	\^	\fIsmall stellated dodecahedron\fR	\^	\^	\^
\^	41	$2| 5#2~5$	$( 5#2 .5. 5#2 .5)$	dodecadodecahedron	\-6	3	45,73
\^	\^	\^	\^	\fImedial rhombic triacontahedron\fR	\^	\^	\^
\^	42	$2~5#2 |5$	$(10.10. 5#2 )$	truncated great dodecahedron	\-6	3	47,75
\^	\^	\^	\^	\fIsmall stellapentakisdodecahedron\fR	\^	\^	\^
\^	43	$ 5#2~5|2$	$(4. 5#2 .4.5)$	rhombidodecadodecahedron	\-6	3	48,76
\^	\^	\^	\^	\fImedial deltoidal hexecontahedron\fR	\^	\^	\^
\^	44	$2~5#2~5|$	$(10.4. 10#9 . 4#3 )$	small rhombidodecahedron	\-18*		46,74
\^	\^	\^	\^	\fIsmall rhombidodecacron\fR	\^	\^	\^
\^	45	$|2~5#2~5$	$(3.3. 5#2 .3.5)$	snub dodecadodecahedron	\-6	3	49,111
\^	\^	\^	\^	\fImedial pentagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 4$	46	$3| 5#3~5$	$( 5#3 .5. 5#3 .5. 5#3 .5)$	ditrigonal dodecadodecahedron	\-16	4	53,80
\^	\^	\^	\^	\fImedial triambic icosahedron\fR	\^	\^	\^
\^	47	$3~5| 5#3$	$( 10#3 .3. 10#3 .5)$	great ditrigonal dodecicosidodecahedron	\-16	4	54,81
\^	\^	\^	\^	\fIgreat ditrigonal dodecacronic hexecontahedron\fR	\^	\^	\^
\^	48	$5#3 ~3|5$	$(10. 5#3 .10.3)$	small ditrigonal dodecicosidodecahedron	\-16	4	55,82
\^	\^	\^	\^	\fIsmall ditrigonal dodecacronic hexecontahedron\fR	\^	\^	\^
\^	49	$5#3~5|3$	$(6. 5#3 .6.5)$	icosidodecadodecahedron	\-16	4	56,83
\^	\^	\^	\^	\fImedial icosacronic hexecontahedron\fR	\^	\^	\^
\^	50	$5#3~3~5|$	$( 10#3 .6.10)$	icositruncated dodecadodecahedron	\-16	4	57,84
\^	\^	\^	\^	\fItridyakisicosahedron\fR	\^	\^	\^
\^	51	$| 5#3~3~5$	$(3. 5#3 .3.3.3.5)$	snub icosidodecadodecahedron	\-16	4	58,112
\^	\^	\^	\^	\fImedial hexagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 6b$	52	$3#2 |3~5$	$(3.5.3.5.3.5)/2$	great ditrigonal icosidodecahedron	\-8	6	61,87
\^	\^	\^	\^	\fIgreat triambic icosahedron\fR	\^	\^	\^
\^	53	$3#2~5|3$	$(6. 3#2 .6.5)$	great icosicosidodecahedron	\-8	6	62,88
\^	\^	\^	\^	\fIgreat icosacronic hexecontahedron\fR	\^	\^	\^
\^	54	$3#2~3|5$	$(10. 3#2 .10.3)$	small icosihemidodecahedron	\-4*		63,89
\^	\^	\^	\^	\fIsmall icosihemidodecacron\fR	\^	\^	\^
\^	55	$3#2~3~5|$	$(10.6. 10#9 . 6#5 )$	small dodecicosahedron	\-28*		64,90
\^	\^	\^	\^	\fIsmall dodecicosacron\fR	\^	\^	\^
_
$I sub 6c$	56	$5#4~5|5$	$(10. 5#4 .10.5)$	small dodecahemidodecahedron	\-12*		65,91
\^	\^	\^	\^	\fIsmall dodecahemidodecacron\fR	\^	\^	\^
_
$I sub 7$	57	$3|2~5#2$	$( 5#2 . 5#2 . 5#2 )$	great stellated dodecahedron	2	7	68,22
\^	\^	\^	\^	\fIgreat icosahedron\fR	\^	\^	\^
\^	58	$5#2 |2~3$	$(3.3.3.3.3)/2$	great icosahedron	2	7	69,41
\^	\^	\^	\^	\fIgreat stellated dodecahedron\fR	\^	\^	\^
\^	59	$2| 5#2~3$	$( 5#2 .3. 5#2 .3)$	great icosidodecahedron	2	7	70,94
\^	\^	\^	\^	\fIgreat rhombic triacontahedron\fR	\^	\^	\^
\^	60	$2~5#2 |3$	$(6.6. 5#2 )$	great truncated icosahedron	2	7	71,95
\^	\^	\^	\^	\fIgreat stellapentakisdodecahedron\fR	\^	\^	\^
\^	61	$2~5#2~3|$	$(6.4. 6#5 . 4#3 )$	rhombicosahedron	\-10*		72,96
\^	\^	\^	\^	\fIrhombicosacron\fR	\^	\^	\^
\^	62	$|2~5#2~3$	$(3.3. 5#2 .3.3)$	great snub icosidodecahedron	2	7	73,113
\^	\^	\^	\^	\fIgreat pentagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 9$	63	$2~5| 5#3$	$( 10#3 . 10#3 . 5)$	small stellated truncated dodecahedron	\-6	9	74,97
\^	\^	\^	\^	\fIgreat pentakisdodekahedron\fR	\^	\^	\^
\^	64	$5#3~2~5|$	$( 10#3 .4.10)$	truncated dodecadodecahedron	\-6	3	75,98
\^	\^	\^	\^	\fImedial disdyakistriacontahedron\fR	\^	\^	\^
\^	65	$| 5#3~2~5$	$(3. 5#3 . 3.3.5)$	inverted snub dodecadodecahedron	\-6	9	76,114
\^	\^	\^	\^	\fImedial inverted pentagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 10a$	66	$5#2~3| 5#3$	$( 10#3 . 5#2 . 10#3 . 3)$	great dodecicosidodecahedron	\-16	10	77,99
\^	\^	\^	\^	\fIgreat dodecacronic hexecontahedron\fR	\^	\^	\^
\^	67	$5#3~5#2 |3$	$(6. 5#3 .6. 5#2 )$	small dodecahemicosahedron	\-8*		78,100
\^	\^	\^	\^	\fIsmall dodecahemicosacron\fR	\^	\^	\^
\^	68	$5#2~5#3~3|$	$(6. 10#3 . 6#5 . 10#7 )$	great dodecicosahedron	\-28*		79,101
\^	\^	\^	\^	\fIgreat dodecicosacron\fR	\^	\^	\^
\^	69	$| 5#3~5#2~3$	$(3. 5#3 .3. 5#2 .3.3)$	great snub dodecicosidodecahedron	\-16	10	80,115
\^	\^	\^	\^	\fIgreat hexagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 10b$	70	$5#4~5|3$	$(6. 5#4 .6.5)$	great dodecahemicosahedron	\-8*		81,102
\^	\^	\^	\^	\fIgreat dodecahemicosacron\fR	\^	\^	\^
_
$I sub 13$	71	$2~3| 5#3$	$( 10#3 . 10#3 .3)$	great stellated truncated dodecahedron	2	13	83,104
\^	\^	\^	\^	\fIgreat triakisicosahedron\fR	\^	\^	\^
\^	72	$5#3~3|2$	$(4. 5#3 .4.3)$	great rhombicosidodecahedron	2	13	84,105
\^	\^	\^	\^	\fIgreat deltoidal hexecontahedron\fR	\^	\^	\^
\^	73	$5#3~2~3|$	$( 10#3 .4.6)$	great truncated icosidodecahedron	2	13	87,108
\^	\^	\^	\^	\fIgreat disdyakistriacontahedron\fR	\^	\^	\^
\^	74	$| 5#3~2~3$	$(3. 5#3 .3.3.3)$	great inverted snub icosidodecahedron	2	13	88,116
\^	\^	\^	\^	\fIgreat inverted pentagonal hexecontahedron\fR	\^	\^	\^
_
$I sub 18a$	75	$5#3~5#2 | 5#3$	$( 10#3 . 5#3 . 10#3 . 5#2 )$	great dodecahemidodecahedron	\-12*		86,107
\^	\^	\^	\^	\fIgreat dodecahemidodecacron\fR	\^	\^	\^
_
$I sub 18b$	76	$3#2~3| 5#3$	$( 10#3 . 3#2 . 10#3 .3)$	great icosihemidodecahedron	\-4*		85,106
\^	\^	\^	\^	\fIgreat icosihemidodecacron\fR	\^	\^	\^
_
$I sub 22$	77	$| 3#2~3#2~5#2$	$(3. 3#2 .3. 3#2 .3.5)$	small retrosnub icosicosidodecahedron	\-8	38	91,118
\^	\^	\^	\^	\fIsmall hexagrammic hexecontahedron\fR	\^	\^	\^
_
$I sub 23$	78	$3#2~5#3~2|$	$(4. 10#3 . 4#3 . 10#7 )$	great rhombidodecahedron 	\-18*		89,109
\^	\^	\^	\^	\fIgreat rhombidodecacron\fR	\^	\^	\^
\^	79	$| 3#2~5#3~2$	$(3. 3#2 .3. 5#3 .3)$	great retrosnub icosidodecahedron	2	37	90,117
\^	\^	\^	\^	\fIgreat pentagrammic hexecontahedron\fR	\^	\^	\^
.TE
.sp 4
.TS
center box ;
cb s s s s s
c|c s|cp-2|c|c|c
c|c s|cp-2|c|c|c
c|c|c|lp-2|c|c|c .
Table 8: Non-Wythoffian Uniform Polyhedra
_
fig	symbol	name	$chi$	$D$	ref
\^	\^	\fIdual\fR	\^	\^	\^
_
80	$| 3#2~5#3~3~5#2$	$(4. 5#3 .4.3.4. 5#2 .4. 3#2 )$	great dirhombicosidodecahedron	\-56		92,119
\^	\^	\^	\fIgreat dirhombicosidodecacron\fR	\^	\^	\^
.TE
