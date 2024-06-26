#import "@preview/polylux:0.3.1": *
#import "@sshwy/notes:0.1.0": *
#import "@preview/cetz:0.1.2"

#set page(paper: "presentation-16-9")
#set text(size: 26pt, font: note_fonts)
#let slide_counter = counter("slides")
#let rbox = block.with(inset: 0.6em, stroke: 2pt, radius: 0.3em)

#let otimes = sym.times.circle
#let sim = sym.tilde
#let bx = math.bold("x")
#let grad = "∇"

#let slide(body) = {
  slide_counter.step()
  polylux-slide({
    body
  })
}

#set page(
  footer: [
    #set align(right)
    #set text(0.7em)
    #counter(page).display(
      "1/1",
      both: true,
    )
    #utils.current-section
  ]
)

#show heading: it => {
  it.body
}
#show link: underline
#show ref: text.with(red)

#slide[
  #align(horizon + center)[
    #text(size: 1.6em, weight: "bold", 
    [SDE and Score-based Diffusion])
    
    Weiyao Huang

    Last Update: #datetime.today().display("[year].[month].[day]")
  ]
]

#set par(justify: true)

#slide[
= Sampling from a distribution

Many of the tasks in the field of generative AI can be formalized
as sampling specific distribution.

#pause

- Image generation: $P_D (X | c)$.
- Text generation: $P_D (X_i | X_1, X_2, ..., X_(i-1))$

// But sampling from a distribution over high-dimensional state-space
]

#slide[
== Inversion Method: 1-Dimensional Case

#figure(block(width: 100%)[
#set math.equation(numbering: none)
#align(center,
cetz.canvas(length: 3cm, {
  import cetz.draw: *

  set-style(
    mark: (fill: black),
    stroke: (thickness: 0.4pt, cap: "round"),
    content: (padding: 1pt)
  )

  // x axis
  line((-2, 0), (2, 0), mark: (end: ">"), stroke: 1pt)

  // y axis
  line((0, -0.2), (0, 1.5), mark: (end: ">"), stroke: 1pt)

  // functions to draw
  let sigma = 0.5
  let mu = 0.0
  import calc: sqrt, exp, pi, pow
  
  let erf(x) = {
    let n_split = 100
    let dt = x / n_split
    let s = 0
    for it in range(n_split) {
      let t = it * dt + 0
      s += exp(-t * t) * dt
    }
    s * 2 / sqrt(pi)
  }

  let funcs = (
    ([Guassian], red, x => {
      1 / (sigma * sqrt(2 * pi)) * exp(
        -0.5 * pow((x - mu) / sigma, 2)
      )
    }), 
    ([Guassian CDF], blue, x => {
      0.5 * (1 + erf((x - mu) / (sigma * sqrt(2))))
    }), 
  )

  // draw functions
  let n_split = 100
  for (name, color, f) in funcs {
    for x in range(n_split) {
      let x_pre = x / n_split * 4 - 2
      let x_nex = (x + 1) / n_split * 4 - 2
      // if not break point
      if calc.abs(f(x_pre) - f(x_nex)) < 0.5 {
        line((x_pre, f(x_pre)), (x_nex, f(x_nex)), stroke: (
          thickness: 2pt,
          paint: color
        ))
      }
    }
  }

  for (y, ct) in ((1, $ 1 $), ) {
    line((3pt, y), (-3pt, y))
    content((), anchor: "right", ct)
  }

}))
])

To sample from $P(X)$:
+ Cumulative distribution func. $Phi(x) = P(X<=x) in [0, 1]$;
+ Sample $Y sim "Uniform"([0, 1])$;
+ Let $X = Phi^(-1) (Y)$.
]

#slide[
== Metropolis-Hastings algorithm (MCMC) @enwiki:1172902257

#only(1)[
(Review of DMS lecture)

To sample $x tilde pi$, we find a $P$ s.t. $pi P = pi$,
and sample from $nu P^n$.

*Theorem of detailed balance*:
If $pi(x) P(y|x) = pi(y) P(x|y)$, then $pi P = pi$.

To construct $P$, let $Q$ be a markov chain: 
$ Q(x|y) > 0 <=> Q(y|x)>0. $
]

#only(2)[
We sample $y tilde Q(dot|x)$, and 
- output $y$ w.p. $a_(x,y)$ (accept);
- or output $x$ w.p. $1-a_(x,y)$ (reject).
where $P(y|x) = a_(x, y) Q(y|x)$ if $x!=y$.

For detailed balance,
$ pi(x) a_(x, y) Q(y|x) = pi(y) a_(y, x) Q(x|y)
. $
Let $a_(x, y) = min( (pi(y) Q(x|y))/(pi(x) Q(y|x)), 1 )$, then
$P$ is constructed.
]
]

#slide[
= Challenges

+ Precise mass func. is often difficult to give.
  Most of the time only samples are given.
+ Hypothesis space is very high dimensional ($10^6$ for image of
  resolution $1024 times 1024$), which leads to very 
  complex distribution.
+ Given samples are often too sparse to "recover" the distribution.
// + Conditional sampling is not straight forward.
]

#slide[
= Power of Differential Methods

Calculate maximal point of $f: RR^s -> RR$?

There are a family of methods called gradient descenting algorithms.

#pause

Sampling by mass func. looks like a randomized version of
maximal point problem.

To achieve that, let's introduce some stochastic differential
gadgets.
]

#slide[
= Stochastic Differential Equation

A general SDE is preseneted @SSarkkaASolin

$ (dif bx)/(dif t) = bold(f)(bx, t)
+ bold(g)(bx, t) bold(w)(t)
. $

$bx(t) in RR^s$, $bold(g)(bx, t) in RR^(s times s)$,
$bold(w)(t) in RR^s$ is a white noise process.

]

#slide[
== White Noise Process

A white noise process $bold(w)(t)$ is a random func. satisfying

+ $bold(w)(t)$ and $bold(w)(t')$ are independent if $t != t'$
  $ EE[bold(w)(t)] = bold(0) . $
  #pause
+ the mapping $t |-> bold(w)(t)$ is a *Guassian process* with zero
  mean Dirac delta correlation @enwiki:1191296053
  $ E[bold(w)(t)bold(w)^T (s)] = delta(t - s) bold(Q) . $
  where $delta(x) tilde.eq cases(+oo quad & x = 0, 0 & x != 0)$,
  $integral_RR delta(x) dif x = 1$; $bold(Q)$ is the spectral
  density.
]

#slide[
#figure(caption: [A possible trajectory of white noise], 
image(width: 65%,"white_noise.png"))
]

#slide[
== Itô Calculus @SSarkkaASolin

$ integral_(t_0)^t bold(g)(bx(t), t) dif bold(beta)(t)
eq.def lim_(n -> oo) sum_(k=1)^n
bold(g)(bx(t_k), t_k) [bold(beta)(t_k) - bold(beta)(t_(k-1))]
. $

where $t_0 < t_1 < dots.c < t_n = t$, $bold(beta): RR -> RR^s$
denotes Brownian motion, a continuous stochastic process:

#pause

+ Brownian motion is nowhere differentiable.
+ White noise can be considered as the formal (or weak) 
  derivative of Brownian motion, 
  $bold(w)(t) = (dif bold(beta)(t))/(dif t)$.
]

#slide[
#figure(caption: [A possible trajectory of Brownian motion], 
image(width: 65%,"brownian.png"))
]

#slide[
== Itô Diffusion

$ dif bx = bold(f)(bx, t) dif t + bold(g)(bx, t) dif bold(beta)
. $

$ bx(t) - bx(t_0) = 
integral_(t_0)^t 
bold(f)(bx(t), t) dif t  +
integral_(t_0)^t bold(g)(bx(t), t) bold(w)(t) dif t 
. $

+ $bold(f)(bx, t)$ is called the _drift function_, which
  determines the nominal dynamics of the system;
+ $bold(g)(bx, t)$ is the _dispersion matrix_, which determines
  how the noise enters the system.
]

#slide[
= Sampling through Stochastic Process

Consider r.v. $bx_"prior"$ drawn from a prior distribution $p_"prior"$, typically a Guassian. Then we
construct a stochastic process for $bx$ so that 
$bx_"target" sim p_"target"$.

#pause

But this kind of process is difficult to construct or learn,
since we know nothing about $p_"target"$.

#pause

Consider another approach: Given $bx_0 sim p_0 = p_"target"$,
construct a process for $bx$ so that $bx_T sim p_T = p_"prior"$,
then we do the reverse process to draw samples.

]

#slide[
== Reversed SDE @ANDERSON1982313

Let's say $bx sim p(bx, t)$. 
Define $bold(G) = bold(g)(bx, t) bold(g)(bx, t)^T$.
then the reversed process is given by
$ dif bx &= overline(bold(f))(bx, t) dif t + 
bold(g)(bx, t) dif overline(bold(beta)) \

overline(f)^i (bx, t) &= f^i (bx, t) - 
[sum_j
grad_(x_j) ln p(bx, t) bold(G)_(i j) +
(diff bold(G)_(i j))/(diff x_j)] \

dif overline(bold(beta)) &= dif bold(beta) + 
1/p(bx, t) sum_(j,k) grad_(x_j) [p(bx, t) g^(j k) (bx, t)] dif t
. $
]


#slide[
== Reversed SDE: Simplified Version

When $bold(g)$ only depends on $t$ and $bold(g) (t) = g(t) I$,
the reversed process is simplified as
$ dif bx &= [bold(f)(bx, t) - g^2 (t) grad ln p(bx, t)] dif t + 
g(t) dif overline(bold(beta)) \

dif overline(bold(beta)) &= dif bold(beta) + g(t)
norm(grad ln p(bx, t))_1 dif t
. $

By simulating this process, we can draw samples $sim p(bx, 0)$.
]

#slide[
  #figure(caption: [Score-based 
  generative modeling through SDEs @song2021scorebased
  ], image("flow.png"))
]

#slide[
== Example I: SMLD @song2021scorebased

Consider the following Markov Chain ($1 <= i <= N$):
$ bx_i = bx_(i - 1) + sqrt(sigma_i^2 - sigma_(i-1)^2) bold(z)_(i-1)
. $
where $bold(z)_(i-1) sim cal(N)(bold(0), bold(I))$.

#pause

Let $N -> +oo$ to make it continuous, the process is given by
$ dif bx = sqrt((dif sigma^2 (t))/(dif t)) dif bold(beta)
. $
]

#slide[
== Example II: DDPM @song2021scorebased

Consider the following Markov Chain ($1 <= i <= N$):
$ bx_i = sqrt(1 - c_i) bx_(i-1) + sqrt(c_i) bold(z)_(i-1)
. $
where $bold(z)_(i-1) sim cal(N)(bold(0), bold(I))$.

#pause

Let $N -> +oo$ to make it continuous, the process is given by
$ dif bx = -1/2 c(t) bx dif t + sqrt(c(t)) dif bold(beta)
. $
]

#slide[
= SDE Simulation

$ dif bx &= [bold(f)(bx, t) - g^2 (t) grad ln p(bx, t)] dif t + 
g(t) dif overline(bold(beta)) 
. $

The remaining problem is: 
+ How to simulate a stochastic process (SDE)?

  #pause
  Brownion motion can be approximated by Guassian kernel.

+ How to calculate $grad ln p(bx, t)$?

  #pause
  Model it using deep neural network.
// $ dif bx = bold(f)(bx, t) dif t + bold(g)(bx, t) dif bold(beta)
// . $
]

#slide[
#set text(size: 18pt)
#bibliography(title: [References], "ref.bib")
]
