/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */

#ifndef nsIRDFCursor_h__
#define nsIRDFCursor_h__

#include "nsISupports.h"
#include "prtypes.h"
#include "rdf.h" // for error codes
class nsIRDFDataSource;
class nsIRDFNode;
class nsIRDFResource;

// 1c2abdb0-4cef-11d2-bc16-00805f912fe7
#define NS_IRDFCURSOR_IID \
{ 0x1c2abdb0, 0x4cef, 0x11d2, { 0xbc, 0x16, 0x00, 0x80, 0x5f, 0x91, 0x2f, 0xe7 } }

/**
 * An abstract base interface that is the basis for all RDF cursors.
 */
class nsIRDFCursor : public nsISupports {
public:
    /**
     * Advance the cursor to the next element.
     * @return NS_ERROR_RDF_CURSOR_EMPTY if the cursor has reached the end
     * and there are no more elements to enumerate; otherwise, NS_OK
     * unless a catastrophic error occurs.
     */
    NS_IMETHOD Advance(void) = 0;
};


// {1ED57100-9904-11d2-8EBA-00805F29F370}
#define NS_IRDFASSERTIONCURSOR_IID \
{ 0x1ed57100, 0x9904, 0x11d2, { 0x8e, 0xba, 0x0, 0x80, 0x5f, 0x29, 0xf3, 0x70 } }

/**
 * A cursor that enumerates assertions
 * @seealso nsIRDFDataSource::GetTargetS(), nsIRDFDataSource::GetSources()
 */
class nsIRDFAssertionCursor : public nsIRDFCursor {
public:
    /**
     * Retrieve the data source in which the assertion actually
     * lives.
     * XXX Is it dangerous to be exposing naked data sources like this?
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetDataSource(nsIRDFDataSource** aDataSource) = 0;

    /**
     * Retrieve the assertion's subject resource.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetSubject(nsIRDFResource** aSubject) = 0;

    /**
     * Retrieve the assertion's predicate resource.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetPredicate(nsIRDFResource** aPredicate) = 0;

    /**
     * Retrieve the assertion's object node.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetObject(nsIRDFNode** aObject) = 0;

    /**
     * Retrieve the assertion's truth value.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetTruthValue(PRBool* aTruthValue) = 0;
};


// {1ED57101-9904-11d2-8EBA-00805F29F370}
#define NS_IRDFARCSOUTCURSOR_IID \
{ 0x1ed57101, 0x9904, 0x11d2, { 0x8e, 0xba, 0x0, 0x80, 0x5f, 0x29, 0xf3, 0x70 } }

/**
 * A cursor that enumerates the outbound arcs from a resource node.
 * @seealso nsIRDFDataSource::ArcsOut()
 */
class nsIRDFArcsOutCursor : public nsIRDFCursor {
public:
    /**
     * Retrieve the data source in which the arc is stored.
     * XXX Is it dangerous to be exposing naked data sources like this?
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetDataSource(nsIRDFDataSource** aDataSource) = 0;

    /**
     * Retrieve the "subject" node from which the arcs originate.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetSubject(nsIRDFResource** aSubject) = 0;

    /**
     * Retrieve the predicate label of the arc.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetPredicate(nsIRDFResource** aPredicate) = 0;

    /**
     * Retrieve the truth value of the arc.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetTruthValue(PRBool* aTruthValue) = 0;
};


// {1ED57102-9904-11d2-8EBA-00805F29F370}
#define NS_IRDFARCSINCURSOR_IID \
{ 0x1ed57102, 0x9904, 0x11d2, { 0x8e, 0xba, 0x0, 0x80, 0x5f, 0x29, 0xf3, 0x70 } }

/**
 * A cursor that enumerates the inbound arcs to a node.
 * @seealso nsIRDFDataSource::ArcsIn()
 */
class nsIRDFArcsInCursor : public nsIRDFCursor {
public:
    /**
     * Retrieve the data source in which the arc is stored.
     * XXX Is it dangerous to be exposing naked data sources like this?
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetDataSource(nsIRDFDataSource** aDataSource) = 0;

    /**
     * Retrieve the "object" node in which the arc terminates.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetObject(nsIRDFNode** aObject) = 0;

    /**
     * Retrieve the predicate label of the arc
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetPredicate(nsIRDFResource** aPredicate) = 0;

    /**
     * Retrieve the truth value of the arc.
     * @return NS_OK, unless a catastrophic error occurs.
     */
    NS_IMETHOD GetTruthValue(PRBool* aTruthValue) = 0;
};


#endif /* nsIRDFCursor_h__ */
