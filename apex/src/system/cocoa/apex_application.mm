#include "apex_application.h"

@implementation ApexApplicationData

@end

@implementation ApexApplication
-(instancetype)initWithData:(ApexApplicationData *)data
{
    self = [super init];
    if (self)
    {
        _data = data;
    }

    return self;
}

-(void) terminate:(id)sender
{
    // TODO: send quit message?
}
@end