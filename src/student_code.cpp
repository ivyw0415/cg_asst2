/*
 * Student solution for CMU 15-462 Project 2 (MeshEdit)
 *
 * Implemented by ____ on ____.
 *
 */

#include "student_code.h"
#include "mutablePriorityQueue.h"

namespace CMU462
{
    bool ifSameVec(Vector3D vec0, Vector3D vec1){
        if (vec0.x == vec1.x && vec0.y==vec1.y && vec0.z==vec1.z)
            return true;
        else
            return false;
    }
    
    bool ifFlipable(EdgeIter e){
        VertexIter v0 = e->halfedge()->next()->next()->vertex();
        VertexIter v1 = e->halfedge()->twin()->next()->next()->vertex();
        HalfedgeIter h = v0->halfedge();
        int i = 1;
        
        do{
            if (h->twin()->vertex() == v1) {
                break;
            }
            h = h->next()->next()->twin();
            i++;
        }while(h != v0->halfedge());
        
        if (i<v0->degree())
            return false;
        else
            return true;
    }
    
    bool ifCollapsable(EdgeIter e){
        if (e->isBoundary()) {
            return false;
        }else if(e->halfedge()->face()->isBoundary()){
            return false;
        }
        else if(e->halfedge()->twin()->face()->isBoundary()){
            return false;
        }
        else if(e->halfedge()->twin()->isBoundary()){
            return false;
        }
        
        VertexIter v0 = e->halfedge()->vertex();
        VertexIter v1 = e->halfedge()->twin()->vertex();
        VertexIter v3 = e->halfedge()->next()->next()->vertex();
        VertexIter v4 = e->halfedge()->twin()->next()->next()->vertex();
        
        if (v3 == v4) {
            return false;
        }else{
            return true;
        }
    }
    
    VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
    {
        // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
        // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.
        if (e0->isBoundary()||e0->halfedge()->face()->isBoundary()) {
            return VertexIter();
        }else{
            HalfedgeIter h0 = e0->halfedge();
            HalfedgeIter h1 = h0->next();
            HalfedgeIter h2 = h1->next();
            HalfedgeIter h3 = h0->twin();
            HalfedgeIter h4 = h3->next();
            HalfedgeIter h5 = h4->next();
            HalfedgeIter h6 = h1->twin();
            HalfedgeIter h7 = h2->twin();
            HalfedgeIter h8 = h4->twin();
            HalfedgeIter h9 = h5->twin();
            
            VertexIter v0 = h0->vertex();
            VertexIter v1 = h3->vertex();
            VertexIter v2 = h2->vertex();
            VertexIter v3 = h5->vertex();
            
            EdgeIter e1 = h1->edge();
            EdgeIter e2 = h2->edge();
            EdgeIter e3 = h4->edge();
            EdgeIter e4 = h5->edge();
            
            FaceIter f0 = h0->face();
            FaceIter f1 = h3->face();
            
            VertexIter v4 = newVertex();
            v4->position = (e0->halfedge()->vertex()->position +
                            e0->halfedge()->twin()->vertex()->position)/2;
            //v4->position = e0->newPosition;
            v4->isNew = true;
            
            
            EdgeIter e5 = newEdge();
            EdgeIter e6 = newEdge();
            EdgeIter e7 = newEdge();
            e5->isNew = true;
            e6->isNew = true;
            //e7->isNew = true;
            e7->isNew = false;
            
            FaceIter f2 = newFace();
            FaceIter f3 = newFace();
            
            HalfedgeIter h10 = newHalfedge();
            HalfedgeIter h11 = newHalfedge();
            HalfedgeIter h12 = newHalfedge();
            HalfedgeIter h13 = newHalfedge();
            HalfedgeIter h14 = newHalfedge();
            HalfedgeIter h15 = newHalfedge();
            
            h0->next() = h1;
            h0->twin() = h3;
            h0->vertex() = v4;
            h0->edge() = e0;
            h0->face() = f0;
            
            h1->next() = h10;
            h1->twin() = h6;
            h1->vertex() = v1;
            h1->edge() = e1;
            h1->face() = f0;
            
            h2->next() = h14;
            h2->twin() = h7;
            h2->vertex() = v2;
            h2->edge() = e2;
            h2->face() = f2;
            
            h3->next() = h11;
            h3->twin() = h0;
            h3->vertex() = v1;
            h3->edge() = e0;
            h3->face() = f1;
            
            h4->next() = h12;
            h4->twin() = h8;
            h4->vertex() = v0;
            h4->edge() = e3;
            h4->face() = f3;
            
            h5->next() = h3;
            h5->twin() = h9;
            h5->vertex() = v3;
            h5->edge() = e4;
            h5->face() = f1;
            
            h6->next() = h6->next();
            h6->twin() = h1;
            h6->vertex() = v2;
            h6->edge() = e1;
            h6->face() = h6->face();
            
            h7->next() = h7->next();
            h7->twin() = h2;
            h7->vertex() = v0;
            h7->edge() = e2;
            h7->face() = h7->face();
            
            h8->next() = h8->next();
            h8->twin() = h4;
            h8->vertex() = v3;
            h8->edge() = e3;
            h8->face() = h8->face();
            
            h9->next() = h9->next();
            h9->twin() = h5;
            h9->vertex() = v1;
            h9->edge() = e4;
            h9->face() = h9->face();
            
            h10->next() = h0;
            h10->twin() = h15;
            h10->vertex() = v2;
            h10->edge() = e6;
            h10->face() = f0;
            
            h11->next() = h5;
            h11->twin() = h12;
            h11->vertex() = v4;
            h11->edge() = e5;
            h11->face() = f1;
            
            h12->next() = h13;
            h12->twin() = h11;
            h12->vertex() = v3;
            h12->edge() = e5;
            h12->face() = f3;
            
            h13->next() = h4;
            h13->twin() = h14;
            h13->vertex() = v4;
            h13->edge() = e7;
            h13->face() = f3;
            
            h14->next() = h15;
            h14->twin() = h13;
            h14->vertex() = v0;
            h14->edge() = e7;
            h14->face() = f2;
            
            h15->next() = h2;
            h15->twin() = h10;
            h15->vertex() = v4;
            h15->edge() = e6;
            h15->face() = f2;
            
            f0->halfedge() = h0;
            f1->halfedge() = h5;
            f2->halfedge() = h14;
            f3->halfedge() = h4;
            
            v0->halfedge() = h14;
            v1->halfedge() = h1;
            v2->halfedge() = h10;
            v3->halfedge() = h8;
            v4->halfedge() = h0;
            
            e0->halfedge() = h0;
            e1->halfedge() = h1;
            e2->halfedge() = h2;
            e3->halfedge() = h4;
            e4->halfedge() = h5;
            e5->halfedge() = h12;
            e6->halfedge() = h10;
            e7->halfedge() = h14;
            
            return v4;
        }
    }
    
    VertexIter HalfedgeMesh::collapseEdge( EdgeIter e )
    {
        // TODO This method should collapse the given edge and return an iterator to the new vertex created by the collapse.
        EdgeIter e0 = e;
        HalfedgeIter h0 = e0->halfedge();
        HalfedgeIter h1 = h0->next();
        HalfedgeIter h2 = h1->next();
        HalfedgeIter h3 = h0->twin();
        HalfedgeIter h4 = h3->next();
        HalfedgeIter h5 = h4->next();
        HalfedgeIter h6 = h5->twin();
        HalfedgeIter h7 = h4->twin();
        HalfedgeIter h8 = h2->twin();
        HalfedgeIter h9 = h1->twin();
        
        HalfedgeIter hl = h8;
        HalfedgeIter hr = h6;
        
        FaceIter f0 = h0->face();
        FaceIter f1 = h3->face();
        FaceIter f2 = h7->face();
        FaceIter f3 = h8->face();
        FaceIter f4 = h9->face();
        FaceIter f5 = h6->face();
        
        VertexIter v0 = h0->vertex();
        VertexIter v1 = h3->vertex();
        VertexIter v2 = h2->vertex();
        VertexIter v3 = h5->vertex();
        
        e0 = h0->edge();
        EdgeIter e1 = h9->edge();
        EdgeIter e2 = h8->edge();
        EdgeIter e3 = h7->edge();
        EdgeIter e4 = h6->edge();
        
        cout<<"collapse start"<<endl;
        
        if (ifCollapsable(e0)) {
            v0->position = (e0->halfedge()->vertex()->position +
                            e0->halfedge()->twin()->vertex()->position)/2;
            
            if (!h8->isBoundary()) {
                h8->twin() = h9;
                h8->vertex() = v0;
                h8->edge() = e2;
                hl = h8;
                do{
                    hl->vertex() = v0;
                    hl = hl->next()->next()->twin();
                }while(hl != h4);
            }else{
                hl = h4;
                h8->vertex() = v0;
                do{
                    hl->vertex() = v0;
                    if (hl->twin()->isBoundary()) {
                        break;
                    }else{
                        hl = hl->twin()->next();
                    }
                }while(hl != h4);
            }
            
            
            if (!h6->isBoundary()) {
                h6->twin() = h7;
                h6->vertex() = v0;
                h6->edge() = e3;
                hr = h6;
                do{
                    hr->vertex() = v0;
                    hr = hr->next()->next()->twin();
                }while(hr != h1);
            }else{
                h6->vertex() = v0;
                hr = h1;
                do{
                    hr->vertex() = v0;
                    if (hr->twin()->isBoundary()) {
                        break;
                    }else{
                        hr = hr->twin()->next();
                    }
                }while(hr != h1);
            }
            
            h7->twin() = h6;
            h7->edge() = e3;
            h7->vertex() = v3;
            
            h9->twin() = h8;
            h9->edge() = e2;
            h9->vertex() = v2;
            
            v0->halfedge() = h8;
            v2->halfedge() = h9;
            v3->halfedge() = h7;
            
            e2->halfedge() = h8;
            e3->halfedge() = h7;
            
            if (!h9->isBoundary()) {
                h9->face()->halfedge() = h9->next();
            }
            if (!h6->isBoundary()) {
                h6->face()->halfedge() = h6->next();
            }
            cout<<"collapse end"<<endl;
            
            deleteVertex(v1);
            
            deleteFace(f0);
            deleteFace(f1);
            
            deleteEdge(e1);
            deleteEdge(e4);
            deleteEdge(e0);
            
            deleteHalfedge(h0);
            deleteHalfedge(h1);
            deleteHalfedge(h2);
            deleteHalfedge(h3);
            deleteHalfedge(h4);
            deleteHalfedge(h5);
            
            return v0;
            
        }else{
            return VertexIter();
        }
    }
    
    EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
    {
        // TODO This method should flip the given edge and return an iterator to the flipped edge.
        if (e0->isBoundary()) {
            return e0;
        }else if(!ifFlipable(e0)){
            return e0;
        }else{
            HalfedgeIter h0 = e0->halfedge();
            HalfedgeIter h1 = h0->next();
            HalfedgeIter h2 = h1->next();
            HalfedgeIter h3 = h0->twin();
            HalfedgeIter h4 = h3->next();
            HalfedgeIter h5 = h4->next();
            HalfedgeIter h6 = h1->twin();
            HalfedgeIter h7 = h2->twin();
            HalfedgeIter h8 = h4->twin();
            HalfedgeIter h9 = h5->twin();
            
            VertexIter v0 = h0->vertex();
            VertexIter v1 = h3->vertex();
            VertexIter v2 = h2->vertex();
            VertexIter v3 = h5->vertex();
            
            EdgeIter e1 = h1->edge();
            EdgeIter e2 = h2->edge();
            EdgeIter e3 = h4->edge();
            EdgeIter e4 = h5->edge();
            
            FaceIter f0 = h0->face();
            FaceIter f1 = h3->face();
            
            /*h0->next() = h1;
             h0->twin() = h3;
             h0->vertex() = v3;
             h0->edge() = e0;
             h0->face() = f0;
             
             h1->next() = h2;
             h1->twin() = h7;
             h1->vertex() = v2;
             h1->edge() = e2;
             h1->face() = f0;
             
             h2->next() = h0;
             h2->twin() = h8;
             h2->vertex() = v0;
             h2->edge() = e3;
             h2->face() = f0;
             
             h3->next() = h4;
             h3->twin() = h0;
             h3->vertex() = v2;
             h3->edge() = e0;
             h3->face() = f1;
             
             h4->next() = h5;
             h4->twin() = h9;
             h4->vertex() = v3;
             h4->edge() = e4;
             h4->face() = f1;
             
             h5->next() = h3;
             h5->twin() = h6;
             h5->vertex() = v1;
             h5->edge() = e1;
             h5->face() = f1;
             
             h6->next() = h6->next();
             h6->twin() = h5;
             h6->vertex() = v2;
             h6->edge() = e1;
             h6->face() = h6->face();
             
             h7->next() = h7->next();
             h7->twin() = h1;
             h7->vertex() = v0;
             h7->edge() = e2;
             h7->face() = h7->face();
             
             h8->next() = h8->next();
             h8->twin() = h2;
             h8->vertex() = v3;
             h8->edge() = e3;
             h8->face() = h8->face();
             
             h9->next() = h9->next();
             h9->twin() = h4;
             h9->vertex() = v1;
             h9->edge() = e4;
             h9->face() = h9->face();
             
             v0->halfedge() = h2;
             v1->halfedge() = h5;
             v2->halfedge() = h3;
             v3->halfedge() = h0;
             
             e0->halfedge() = h0;
             e1->halfedge() = h6;
             e2->halfedge() = h1;
             e3->halfedge() = h2;
             e4->halfedge() = h8;*/
            
            h0->next() = h2;
            h0->edge() = e0;
            h0->vertex() = v3;
            h0->twin() = h3;
            h0->face() = f0;
            
            h2->next() = h4;
            h2->face() = f0;
            
            h4->next() = h0;
            h4->face() = f0;
            
            h3->next() = h5;
            h3->twin() = h0;
            h3->vertex() = v2;
            h3->face() = f1;
            h3->edge() = e0;
            
            h1->next() = h3;
            h1->face() = f1;
            
            h5->next() = h1;
            h5->face() = f1;
            
            e0->halfedge() = h0;
            
            v0->halfedge() = h4;
            v1->halfedge() = h1;
            v2->halfedge() = h2;
            v3->halfedge() = h5;
            
            f0->halfedge() = h0;
            f1->halfedge() = h3;
            
            return e0;
        }
    }
    
    bool ifFlip(EdgeIter e){
        if(e->isNew == true){
            if ((e->halfedge()->vertex()->isNew == true && e->halfedge()->twin()->vertex()->isNew == false ) ||
                (e->halfedge()->vertex()->isNew == false && e->halfedge()->twin()->vertex()->isNew == true))
            {
                return true;
            }else{
                return false;
            }
        }
        return false;
    }
    
    void MeshResampler::upsample( HalfedgeMesh& mesh )
    // This routine should increase the number of triangles in the mesh using Loop subdivision.
    {
        // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
        // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
        // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
        // the new subdivided (fine) mesh, which has more elements to traverse.  We will then assign vertex positions in
        // the new mesh based on the values we computed for the original mesh.
        
        
        // TODO Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
        // TODO and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
        // TODO a vertex of the original mesh.
        // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
        // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
        // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
        // the new subdivided (fine) mesh, which has more elements to traverse.  We will then assign vertex positions in
        // the new mesh based on the values we computed for the original mesh.
        
        
        // TODO Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
        // TODO and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
        // TODO a vertex of the original mesh.
        
        VertexIter v = mesh.verticesBegin();
        while (v != mesh.verticesEnd()) {
            v->isNew = false;
            VertexIter nextV = v;
            nextV++;
            Vector3D vPos = Vector3D();
            HalfedgeIter h = v->halfedge();
            do{
                vPos += h->next()->vertex()->position;
                h = h->next()->next()->twin();
            }while(h != v->halfedge());
            
            if ((int)v->degree() == 3) {
                v->newPosition = 3.0/16.0*vPos+(1-9.0/16.0)*v->position;
            }else{
                v->newPosition = (3.0/8.0/v->degree())*(vPos)+(5.0/8.0)*v->position;
            }
            v = nextV;
        }
        // TODO Next, compute the updated vertex positions associated with edges, and store it in Edge::newPosition.
        // TODO Next, we're going to split every edge in the mesh, in any order.  For future
        // TODO reference, we're also going to store some information about which subdivided
        // TODO edges come from splitting an edge in the original mesh, and which edges are new,
        // TODO by setting the flat Edge::isNew.  Note that in this loop, we only want to iterate
        // TODO over edges of the original mesh---otherwise, we'll end up splitting edges that we
        // TODO just split (and the loop will never end!)
        
        EdgeIter e = mesh.edgesBegin();
        int edgeNum = mesh.nEdges();
        while(e != mesh.edgesEnd())
        {
            e->isNew = false;
            EdgeIter nextEdge = e;
            nextEdge++;
            e->newPosition = (3.0/8.0*(e->halfedge()->vertex()->position + e->halfedge()->twin()->vertex()->position) + 1.0/8.0*(e->halfedge()->next()->next()->vertex()->position + e->halfedge()->twin()->next()->next()->vertex()->position));
            e = nextEdge;
        }
        
        
        e = mesh.edgesBegin();
        int i = 0;
        while (i<edgeNum)
        {
            EdgeIter nextEdge = e;
            nextEdge++;
            if (e->isNew == false) {
                mesh.splitEdge(e)->newPosition = e->newPosition;
            }
            e = nextEdge;
            i++;
        }
        
        // TODO Now flip any new edge that connects an old and new vertex.
        e = mesh.edgesBegin();
        while(e != mesh.edgesEnd()){
            EdgeIter nextEdge = e;
            nextEdge++;
            if (ifFlip(e)) {
                mesh.flipEdge(e);
            }
            e = nextEdge;
        }
        
        // TODO Finally, copy the new vertex positions into final Vertex::position.
        v = mesh.verticesBegin();
        while (v != mesh.verticesEnd()){
            VertexIter nextV = v;
            nextV++;
            v->position = v->newPosition;
            v = nextV;
        }
        
    }
    
    // Given an edge, the constructor for EdgeRecord finds the
    // optimal point associated with the edge's current quadric,
    // and assigns this edge a cost based on how much quadric
    // error is observed at this optimal point.
    EdgeRecord::EdgeRecord( EdgeIter& _edge )
    : edge( _edge )
    {
        // TODO Compute the combined quadric from the edge endpoints.
        VertexIter v0 = _edge->halfedge()->vertex();
        VertexIter v1 = _edge->halfedge()->twin()->vertex();
        Matrix4x4 quadric = v0->quadric + v1->quadric;
        //cout<<":) ";
        
        // TODO Build the 3x3 linear system whose solution minimizes
        // the quadric error associated with these two endpoints.
        Matrix3x3 A; // computed by accumulating quadrics and then extacting the upper-left 3x3 block
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                A(i,j) = quadric(i,j);
            }
        }
        Vector3D b = quadric.column(3).to3D();  // computed by extracting minus the upper-right 3x1 column from the same matrix
        b = -b;
        Vector3D x = A.inv() * b; // solve Ax = b for x, by hitting both sides with the inverse of A
        Vector4D x_(x.x,x.y,x.z,1);
        // TODO Use this system to solve for the optimal position, and
        // TODO store it in EdgeRecord::optimalPoint.
        optimalPoint = x;
        edge = _edge;
        
        // TODO Also store the cost associated with collapsing this edge
        // TODO in EdgeRecord::Cost.
        score = dot(x_, quadric * x_);
    }
    
    void MeshResampler::downsample( HalfedgeMesh& mesh )
    {
        // TODO Compute initial quadrics for each face by simply writing the plane
        // equation for the face in homogeneous coordinates.  These quadrics should
        // be stored in Face::quadric
        FaceIter f = mesh.facesBegin();
        while (f!=mesh.facesEnd()) {
            FaceIter nextF = f;
            nextF++;
            double d = dot(f->normal(), f->halfedge()->vertex()->position);
            d = -d;
            Vector4D v(f->normal().x, f->normal().y, f->normal().z, d);
            f->quadric = outer(v, v);
            f = nextF;
        }
        
        // TODO Compute an initial quadric for each vertex as the sum of the quadrics
        // associated with the incident faces, storing it in Vertex::quadric
        VertexIter v = mesh.verticesBegin();
        while (v != mesh.verticesEnd()){
            VertexIter nextV = v;
            nextV++;
            HalfedgeIter h = v->halfedge();
            HalfedgeIter h_tmp = h;
            do{
                v->quadric += h->face()->quadric;
                h = h->twin()->next();
            }while(h!=h_tmp);
            v = nextV;
        }
        
        // TODO Build a priority queue of edges according to their quadric error cost,
        // TODO i.e., by building an EdgeRecord for each edge and sticking it in the queue.
        MutablePriorityQueue<EdgeRecord> queue;
        EdgeIter e = mesh.edgesBegin();
        while(e != mesh.edgesEnd()){
            EdgeIter nextE = e;
            nextE++;
            EdgeRecord nRecord( e );
            e->record = nRecord;
            queue.insert( e->record );
            e = nextE;
        }
        
        
        // TODO Until we reach the target edge budget, collapse the best edge.  Remember
        // TODO to remove from the queue any edge that touches the collapsing edge BEFORE
        // TODO it gets collapsed, and add back into the queue any edge touching the collapsed
        // TODO vertex AFTER it's been collapsed.  Also remember to assign a quadric to the
        // TODO collapsed vertex, and to pop the collapsed edge off the top of the queue
        
        int faceN = mesh.nFaces();
        int iter=0;
        while (mesh.nFaces()>faceN/4.0 && mesh.nFaces()>4 && !queue.isEmpty()) {
            //for (int iter = 0; iter < 100; iter ++) {
            EdgeRecord bestEdge = queue.top();
            queue.pop();
            //cout<<bestEdge.edge->quadrics<<endl;
            //cout<<mesh.nFaces()<<endl;
            
            // TODO to remove from the queue any edge that touches the collapsing edge BEFORE
            // TODO it gets collapsed,
            VertexIter ver0 = bestEdge.edge->halfedge()->vertex();
            VertexIter ver1 = bestEdge.edge->halfedge()->twin()->vertex();
            Matrix4x4 nQuad = ver0->quadric + ver1->quadric;
            
            HalfedgeIter h0 = ver0->halfedge();
            HalfedgeIter h0_tmp = h0;
            HalfedgeIter h1 = ver1->halfedge();
            HalfedgeIter h1_tmp = h1;
            do{
                queue.remove(h0->edge()->record);
                h0 = h0->twin()->next();
            }while(h0 != h0_tmp);
            do{
                queue.remove(h1->edge()->record);
                h1 = h1->twin()->next();
            }while(h1 != h1_tmp);
            iter++;
            
            cout<<iter<<endl;
            
            if(ifCollapsable(bestEdge.edge)){
                //cout<<"XD "<<iter<<endl;
                VertexIter newV = mesh.collapseEdge(bestEdge.edge);
                newV->position = bestEdge.optimalPoint;
                newV->quadric = nQuad;
                HalfedgeIter h2 = newV->halfedge();
                HalfedgeIter h2_tmp = h2;
                do{
                    EdgeIter iEdge = h2->edge();
                    EdgeRecord _nRecord( iEdge );
                    iEdge->record = _nRecord;
                    queue.insert( iEdge->record );
                    h2 = h2->twin()->next();
                }while(h2 != h2_tmp);
            }
        }
    }
    
    void Vertex::computeCentroid( void )
    {
        // TODO Compute the average position of all neighbors of this vertex, and
        // TODO store it in Vertex::centroid.  This value will be used for resampling.
        Vector3D vCen = Vector3D(0,0,0);
        HalfedgeIter h = halfedge();
        do{
            vCen += h->twin()->vertex()->position;
            h = h->twin()->next();
        }while(h!=halfedge());
        vCen = vCen/degree();
        centroid = vCen;
    }
    
    Vector3D Vertex::normal( void ) const
    // TODO Returns an approximate unit normal at this vertex, computed by
    // TODO taking the area-weighted average of the normals of neighboring
    // TODO triangles, then normalizing.
    {
        // TODO Compute and return the area-weighted unit normal.
        
        double area = 0;
        Vector3D n = Vector3D(0,0,0);
        HalfedgeIter h = _halfedge;
        do{
            Vector3D e0 = - h->vertex()->position + h->next()->vertex()->position;
            Vector3D e1 = - h->next()->vertex()->position + h->next()->next()->vertex()->position;
            Vector3D crsPrd = cross(e0, e1);
            n += crsPrd;
            h = h->twin()->next();
        }while(h != _halfedge);
        Vector3D unit_normal = n;
        unit_normal.normalize();
        return unit_normal;
    }
    
    void MeshResampler::resample( HalfedgeMesh& mesh )
    {
        // TODO Compute the mean edge length.
        double mean = 0;
        EdgeIter e = mesh.edgesBegin();
        while (e!=mesh.edgesEnd()) {
            mean += e->length();
            e++;
        }
        mean = mean/mesh.nEdges();
        
        // TODO Repeat the four main steps for 5 or 6 iterations
        for (int i=0; i<6; i++) {
            // TODO Split edges much longer than the target length (being careful about how the loop is written!)
            // TODO Collapse edges much shorter than the target length.
            EdgeIter e = mesh.edgesBegin();
            while (e!=mesh.edgesEnd()) {
                EdgeIter nextE = e;
                nextE++;
                if (e->length()>(4.0*mean/3.0)) {
                    mesh.splitEdge(e);
                }
                e = nextE;
            }
            
            
            // TODO Split edges much longer than the target length (being careful about how the loop is written!)
            // TODO Collapse edges much shorter than the target length.  Here we need to be EXTRA careful about
            // TODO advancing the loop, because many edges may have been destroyed by a collapse (which ones?)
            MutablePriorityQueue<EdgeIter> queue;
            for (EdgeIter e = mesh.edgesBegin(); e!=mesh.edgesEnd(); e++) {
                if (e->length()<(4.0*mean/5.0)) {
                    queue.insert(e);
                }
            }
            
            while (!queue.isEmpty()) {
                EdgeIter e = queue.top();
                queue.pop();
                
                VertexIter ver0 = e->halfedge()->vertex();
                VertexIter ver1 = e->halfedge()->twin()->vertex();
                
                HalfedgeIter h0 = ver0->halfedge();
                HalfedgeIter h0_tmp = h0;
                HalfedgeIter h1 = ver1->halfedge();
                HalfedgeIter h1_tmp = h1;
                do{
                    queue.remove(h0->edge());
                    h0 = h0->twin()->next();
                }while(h0 != h0_tmp);
                do{
                    queue.remove(h1->edge());
                    h1 = h1->twin()->next();
                }while(h1 != h1_tmp);
                
                mesh.collapseEdge(e);
            }
            
            // TODO Now flip each edge if it improves vertex degree
            e = mesh.edgesBegin();
            while (e!=mesh.edgesEnd()) {
                EdgeIter nextE = e;
                nextE++;
                HalfedgeIter h0 = e->halfedge();
                HalfedgeIter h1 = e->halfedge()->twin();
                
                int a1 = h0->vertex()->degree();
                int a2 = h1->vertex()->degree();
                int b1 = h0->next()->next()->vertex()->degree();
                int b2 = h1->next()->next()->vertex()->degree();
                
                int init_dev = abs(a1-6)+abs(a2-6)+abs(b1-6)+abs(b2-6);
                int aft_dev = abs(a1-7)+abs(a2-7)+abs(b1-5)+abs(b2-5);
                
                if (aft_dev<init_dev) {
                    mesh.flipEdge(e);
                }
                e = nextE;
            }
            
            // TODO Finally, apply some tangential smoothing to the vertex positions
            for (int i=0; i<20; i++) {
                VertexIter v = mesh.verticesBegin();
                while (v!=mesh.verticesEnd()) {
                    VertexIter nextV = v;
                    nextV++;
                    v->computeCentroid();
                    v = nextV;
                }
                
                v = mesh.verticesBegin();
                while (v!=mesh.verticesEnd()) {
                    VertexIter nextV = v;
                    nextV++;
                    Vector3D q = Vector3D(0,0,0);
                    Vector3D p = v->position;
                    Vector3D c = v->centroid;
                    Vector3D dir = c-p;
                    dir = dir - dot(v->normal(),dir)*v->normal();
                    q = p + 0.2*dir;
                    v->position = q;
                    v = nextV;
                }
            }
        }
    }
}
