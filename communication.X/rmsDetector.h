/* 
 * File:   rmsDetector.h
 * Author: nathdwek
 *
 * Created on 24 avril 2015, 11:12
 */

#ifndef RMSDETECTOR_H
#define	RMSDETECTOR_H

#define MIN_RMS_VALUE 270

void initRmsDetector();
char rmsDetect(long filteredSample[2],char detected[2]);


#endif	/* RMSDETECTOR_H */

