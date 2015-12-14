===============
vmod_vsthrottle
===============

-------------------------
Varnish Throttling Module
-------------------------

:Author: Dag Haavi Finstad
:Date: 2015-12-14
:Version: 1.0.1
:Manual section: 3

SYNOPSIS
========

import vsthrottle;

DESCRIPTION
===========

A Varnish vmod for rate-limiting traffic on a single Varnish
server. Offers a simple interface for throttling traffic on a per-key
basis to a specific request rate.

Keys can be specified from any VCL string, e.g. based on client.ip, a
specific cookie value, an API token, etc.

The request rate is specified as the number of requests permitted over
a period. To keep things simple, this is passed as two separate
parameters, 'limit' and 'period'.

This VMOD implements a `token-bucket algorithm`_. State associated
with the token bucket for each key is stored in-memory using BSD's
red-black tree implementation.

Memory usage is around 100 bytes per key tracked.

.. _token-bucket algorithm: http://en.wikipedia.org/wiki/Token_bucket


FUNCTIONS
=========

is_denied
---------

Prototype
        ::

                is_denied(STRING key, INT limit, DURATION period)
Arguments
	key: A unique identifier to define what is being throttled - more examples below
	
	limit: How many requests in the specified period
	
	period: The time period
	
Return value
	BOOL
Description
	Can be used to rate limit the traffic for a specific key to a
	maximum of 'limit' requests per 'period' time. A token bucket
	is uniquely identified by the triplet of its key, limit and
	period, so using the same key multiple places with different
	rules will create multiple token buckets.

Example
        ::

		sub vcl_recv {
			if (vsthrottle.is_denied(client.identity, 15, 10s)) {
				# Client has exceeded 15 reqs per 10s
				return (synth(429, "Too Many Requests"));
			}

			# ...
		}


INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

This VMOD is written for Varnish Cache 4.1.

Pre-installation configuration::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For example, when varnishd configure was called
with ``--prefix=$PREFIX``, use

 PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
 export PKG_CONFIG_PATH

Make and install the vmod::
 
 make           # builds the vmod
 make install   # installs your vmod in `VMODDIR`
 make check     # runs the unit tests in ``src/tests/*.vtc``
 
The libvmod-vsthrottle vmod will now be available in your VMODDIR and
can be copied to other systems as required.

 
USAGE
=====

In your VCL you can now use this vmod along the following lines::
        
        import vsthrottle;
        
        sub vcl_recv {
        	if (vsthrottle.is_denied(client.identity, 15, 10s)) {
        		# Client has exceeded 15 reqs per 10s
        		return (synth(429, "Too Many Requests"));
        	}
        } 

