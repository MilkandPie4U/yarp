// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Author: Lorenzo Natale
 * Copyright (C) 2007, 2010 The RobotCub Consortium
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __YARP_SIG_RAND__
#define __YARP_SIG_RAND__

#include <yarp/sig/Vector.h>

namespace yarp
{
    namespace math
    {
        /** 
        * This class groups routines for random number generation.
        */
        class Rand;

        /**
         * Some helpers for internal use by yarp::math classes. Without much work
         * these classes could be made available to users (in the yarp::math namespace).
         * For now they should be considered only for internal usage.
         */
        namespace impl {
            class RandScalar;
            class RandnScalar;
            class RandVector;
            class RandnVector;
        }
    }
};

/**
* A random number generator, uniform in the range 0-1.
*/
class yarp::math::impl::RandScalar
{
    void *impl;
    int seed;
    RandScalar(const RandScalar &l); 
public:
     RandScalar(int seed);
     RandScalar();
     ~RandScalar();

    /**
    * Initialize the random generator using
    * current time (time(0)).
    */
     void init();

    /**
    * Initialize the random generator.
    * @param seed the seed.
    */
     void init (int seed);

    /**
    * Get the seed.
    * @return the seed.
    */
     int getSeed ()
     { return seed; }

    /**
    * Generate a random number from a 
    * uniform distribution.
    * @return the random value.
    */
     double get();

    /**
    * Generate a random number from a 
    * uniform distribution within [min, max]
    * @return the random value.
    */
     double get(double min, double max);
};

/**
* A class to generate random vectors, uniform distribution.
*/
class yarp::math::impl::RandVector
{
    yarp::sig::Vector data;
    RandScalar rnd;

private:
    RandVector(const RandVector &l);

public:
    RandVector(int s);

    void resize(int s);
    void init();
    void init(int seed);

    const yarp::sig::Vector &get();
    const yarp::sig::Vector &get(const yarp::sig::Vector &min, const yarp::sig::Vector &max);
};

/**
* A random number generator, normal distribution.
*/
class yarp::math::impl::RandnScalar
{
private:
    inline void boxMuller();
    double y[2];
    int last;

    RandScalar rnd;
    RandnScalar(const RandnScalar &l);
public:
    /**
    * Constructor.
    */
    RandnScalar();
    
    /**
    * Constructor, initialize the generator.
    * @param seed, seed for the rnd generator.
    */
    RandnScalar(int seed);

    /**
    * Inizialize the generator.
    * Uses current time for the seed.
    */
    void init();

    /**
    * Inizialize the generator.
    * Provide a seed.
    * @param seed the seed
    */
    void init (int seed);

    long getSeed ()
    { return rnd.getSeed(); }

    /**
    * Generate a randomly generated number, drawn from
    * a normal distribution.
    * @return the random number.
    */
    double get();
};

/**
* A class to generate random vectors, normal distribution.
*/
class yarp::math::impl::RandnVector
{
    yarp::sig::Vector data;
    RandnScalar rnd;
    RandnVector(const RandnVector &l){};

public:
    RandnVector(int s);

    void resize(int s);
    void init();
    void init(int seed);

    const yarp::sig::Vector &get();
};

/**
* A static class grouping function for random number 
* generator. Thread safe.
*
* Methods inside this class provides access to a global instance 
* of on object that generates random numbers. This class in turn 
* is a simple wrapper around gsl routines. This probably provides
* an excellent source of random numbers, but if you are picky about 
* random number generation we recommend you read the gsl documentation 
* (see below) or implement your own routines.
* 
* The initialization routine of the generator is basically:
*
* gsl_rng_env_setup();
* T=gsl_rng_default;
* r=gsl_rng_alloc(T);
*
* gsl_rng_set(T, seed);
* 
* which means that the behavior of the random generator can be configured
* through the environment variables GSL_RNG_TYPE as described in the GSL 
* documentation. The genrator is alwasy initialized with a seed equal to the
* current time. You can reset the seed by explicitly calling Rand::init(seed).
*
* Default generator is gsl_rng_mt19937.
*
* See http://www.gnu.org/software/gsl/manual/html_node/Random-Number-Generation.html
* for more information.
* 
*/
class yarp::math::Rand
{
public:
    /**
    * Get a random number from a uniform distribution
    * in the range [0,1].
    */
    static double scalar();

    /**
    * Get a random number from a uniform distribution
    * in the range [min,max].
    * @param min lower bound
    * @param max upper bound
    * @return return value
    */
    static double scalar(double min, double max);

    /**
    * Get a vector of random numbers from a uniform distribution,
    * values are in the range [0, 1].
    * @param s the size of the vector
    * @return the random vector
    */
    static yarp::sig::Vector vector(int s);

    /**
    * Get a vector of random numbers from a uniform distribution,
    * values are in the range [min, max], for each components. The
    * function determines the size of the vector from the parameters.
    * @param min a vector whose components specify the lower bound of 
    * the distribution.
    * @param max a vector whose components specify the upper bound of
    * the distribution
    * @return the random vector
    */
    static yarp::sig::Vector vector(const yarp::sig::Vector &min,
                                    const yarp::sig::Vector &max);

    /**
    * Initialize the random number generator, with
    * current time (time(0)).
    */
    static void init();
    
    /**
    * Initialize the random number generator, provide
    * a seed.
    * @param seed: a seed.
    */
    static void init(int seed);
};

#endif
