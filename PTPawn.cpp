#include "PTPawn.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputComponent.h"
#include "PTPlayerController.h"

APTPawn::APTPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    // 충돌 캡슐 (루트 컴포넌트로 설정)
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    SetRootComponent(BoxComp);
    BoxComp->SetSimulatePhysics(false);
    /*BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));*/
   

    // Skeletal Mesh 설정
    SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMeshComp->SetupAttachment(BoxComp);
    SkeletalMeshComp->SetSimulatePhysics(false);

    // 카메라 붐 (스프링암)
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(BoxComp);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true; // 마우스 회전에 따라 카메라 회전

    // 카메라
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
    CameraComp->bUsePawnControlRotation = false;


 }

void APTPawn::BeginPlay()
{
    Super::BeginPlay();
}

void APTPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (APTPlayerController* PlayerController = Cast<APTPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &APTPawn::Move); //APTPawn 대신 ThisClass 가능
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &APTPawn::Look);
            }
         }
    }
}


void APTPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


// 이동 함수
void APTPawn::Move(const FInputActionValue& Value)
{
    FVector2D MoveInput = Value.Get<FVector2D>();
    
    AddActorLocalOffset(FVector(MoveInput.X, MoveInput.Y, 0.f)* MoveSpeed* GetWorld()->GetDeltaSeconds());
    //AddActorWorldOffset(FVector(MoveInput.X, MoveInput.Y, 0.f) * MoveSpeed * GetWorld()->GetDeltaSeconds());
}

// 회전 함수(카메라 회전)
void APTPawn::Look(const FInputActionValue& value)
{
    FVector2D LookInput = value.Get<FVector2D>();
    //UE_LOG(LogTemp, Warning, TEXT("LookInput: %.1f"), LookInput);

    AddActorLocalRotation(FRotator(-LookInput.Y, LookInput.X, 0.f));
    //AddActorWorldRotation(FRotator(-LookInput.Y, LookInput.X, 0.f));
}





/*void APTPawn::Move(const FInputActionValue& Value)
{
    if (!Controller) return;

    FVector2D MoveInput = Value.Get<FVector2D>();
    FVector MoveDirection = FVector::ZeroVector;

    if (!FMath::IsNearlyZero(MoveInput.X) || !FMath::IsNearlyZero(MoveInput.Y))
    {
        //카메라의 Pitch와 Yaw을 모두 반영
        FRotator CameraRotation = CameraComp->GetComponentRotation();
        FRotationMatrix CameraMatrix(CameraRotation);

        // 카메라의 앞/오른쪽 방향 벡터 가져오기
        FVector ForwardDirection = CameraMatrix.GetUnitAxis(EAxis::X);
        FVector RightDirection = CameraMatrix.GetUnitAxis(EAxis::Y);

        // 입력값을 이동 벡터에 적용
        MoveDirection = (ForwardDirection * MoveInput.X) + (RightDirection * MoveInput.Y);
        MoveDirection.Normalize();

        // **월드 좌표 기준으로 이동**
        AddActorWorldOffset(MoveDirection * MoveSpeed * GetWorld()->GetDeltaSeconds(), true);
    }
}



void APTPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookInput = Value.Get<FVector2D>();

    // 회전 계산
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += LookInput.X * LookSensitivity;
    NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - LookInput.Y * LookSensitivity, -89.0f, 89.0f);

    SetActorRotation(NewRotation);
}*/