#include "apex_application.h"

@implementation ApexApplicationData

@end

@implementation ApexApplication2
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

-(void)sendEvent:(NSEvent *)event
{
    [super sendEvent:event];
}
@end