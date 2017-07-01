# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## General Formula for PID Control
![PID Formula](https://wikimedia.org/api/rest_v1/media/math/render/svg/242b6798586d4fc1aedf7e4f92bf77416e4fc76c)
---
| P Control        | PD Control           | PID Control |
| ------------- |:-------------:| -----:|
| ![P Control](https://github.com/zeeshananjumjunaidi/pid-controller/blob/master/data/P-Controller.gif)      | ![P Control](https://github.com/zeeshananjumjunaidi/pid-controller/blob/master/data/PD-Controller.gif) | ![P Control](https://github.com/zeeshananjumjunaidi/pid-controller/blob/master/data/PID-Controller.gif) |
---
| P        | D         | I  |
| ------------- |:-------------:| -----:|
| P value update itself based on the actual error, more error high value and vise versa   | D term based on the current rate of change of cte     |   I term use past cte, e.g. if the output is weak, then the integral of all error over time will respond with a strong action.  |
---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
